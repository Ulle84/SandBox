#include <QDebug>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QSettings>
#include <QList>
#include <QPair>
#include <QStringList>

#include "ClassAnalyzer.h"

ClassAnalyzer::ClassAnalyzer()
{

}

ClassAnalyzer::~ClassAnalyzer()
{

}

void ClassAnalyzer::parseFolder(const QString& folder)
{
  parseFolders(QStringList() << folder);
}

void ClassAnalyzer::parseFolders(const QStringList& folders)
{
  m_classes.clear();

  for (auto it = folders.begin(); it != folders.end(); it++)
  {
    QDirIterator it2(*it, QStringList() << "*.h", QDir::Files, QDirIterator::Subdirectories);

    while (it2.hasNext())
    {
      parseFile(it2.next());
    }

  }

  postProcessBaseClasses();

  printAllClasses();

  printFilesWithMoreThanOneClassDeclaration();
}

void ClassAnalyzer::removeComments(QString& code)
{
  // DO NOT CHANGE ORDER!!!
  removeSequences(code, "//*", "\n", false);
  removeSequences(code, "/*", "*/");
  removeSequences(code, "//", "\n", false);
}

void ClassAnalyzer::removeSequences(QString& code, const QString& startTag, const QString& endTag, bool removeEndTag)
{
  int positionStart = code.indexOf(startTag);
  int positionEnd = -1;

  while (positionStart > -1)
  {
    // handle special case '//*'
    /*if (startTag == "/*" && positionStart != 0)
    {
      if (code[positionStart - 1] == '/')
      {
        positionStart++; // otherwise we will run in endless loop
        positionStart = code.indexOf(startTag, positionStart);
        continue;
      }
    }*/

    positionEnd = code.indexOf(endTag, positionStart + 1);

    if (positionStart < positionEnd)
    {
      int length = positionEnd - positionStart;

      if (removeEndTag)
      {
        length += endTag.length();
      }

      code = code.remove(positionStart, length);
    }
    else
    {
      positionStart++; // otherwise we will run in endless loop
    }

    positionStart = code.indexOf(startTag, positionStart);

  }
}

void ClassAnalyzer::parseFile(const QString& fileName)
{
  //qDebug() << "parsing file: " << fileName;
  m_currentFile = fileName;

  QFile file(fileName);

  if (!file.open(QFile::ReadOnly | QFile::Text))
  {
    qDebug() << "could not open file: " << fileName;
  }

  QTextStream in(&file);
  QString code = in.readAll();

  removeComments(code);

  /*QFile fileOut(fileName + "_removedComments");

  if (!fileOut.open(QFile::WriteOnly | QFile::Text))
  {
    qDebug() << "could not open file: " << fileName;
  }

  QTextStream out(&fileOut);
  out << code;
  fileOut.close();*/

  parseNamespaces(code);

  int position = 0;

  int numberOfClassDeclarationsPerFile = 0;
  while (position > -1)
  {    
    position = code.indexOf(QRegExp("\\sclass\\s"), position + 1);

    if (position > -1)
    {
      position += 5;

      int posNextSemicolon = code.indexOf(";", position);
      int posNextOpeningCurlyBracket = code.indexOf("{", position);
      int posNextClosingRoundBracket = code.indexOf(")", position);
      int posNextClosingAngleBracket = code.indexOf(">", position);
      int posNextColon = code.indexOf(":", position);

      if (posNextOpeningCurlyBracket < 0)
      {
        //qDebug() << "no class body found";
        continue;
      }

      if (posNextSemicolon < posNextOpeningCurlyBracket)
      {
        //qDebug() << "ignore forward declaration, typedefs etc.";
        continue;
      }

      if (posNextClosingRoundBracket > -1 && posNextClosingRoundBracket < posNextOpeningCurlyBracket)
      {
        if (!(posNextColon > -1 && posNextColon < posNextOpeningCurlyBracket))
        {
          //qDebug() << "ignore parameter etc.";
          continue;
        }
      }

      if (posNextClosingAngleBracket > -1 && posNextClosingAngleBracket < posNextOpeningCurlyBracket)
      {
        if (posNextColon > -1 && posNextColon < posNextOpeningCurlyBracket)
        {
          if (posNextClosingAngleBracket < posNextColon)
          {
            //qDebug() << "ignore template parameters";
            continue;
          }
        }
        else
        {
          //qDebug() << "ignore template parameters";
          continue;
        }
      }

      numberOfClassDeclarationsPerFile++;

      QString classDeclaration = code.mid(position, posNextOpeningCurlyBracket - position);
      removeSequences(classDeclaration, "<", ">");

      parseClassDeclaration(classDeclaration.simplified(), position);
    }
  }

  m_numberOfClassesPerFile.insert(numberOfClassDeclarationsPerFile, fileName);

  //qDebug() << "finished parsing file";
}

void ClassAnalyzer::parseClassDeclaration(const QString& classDeclaration, int position)
{
  //qDebug() << "parsing class declaration: " << classDeclaration;

  QString className;
  QStringList baseClassNames;

  QString copy = classDeclaration;

  copy = copy.replace(":", " : ");
  copy = copy.replace(" :  : ", "::");


  if (copy.contains(" : "))
  {
    QStringList tokens = copy.split(" : ", QString::SkipEmptyParts);

    if (tokens.size() != 2)
    {
      return;
    }

    className = parseClassName(tokens.first());
    baseClassNames = parseBaseClassNames(tokens.last());
  }
  else
  {
    className = parseClassName(classDeclaration);
  }

  if (className.isEmpty())
  {
    return;
  }

  className.prepend(getNamespacePrefix(position));

  Class c(className);

  c.setBaseClasses(baseClassNames);
  c.setHeader(m_currentFile);

  m_classes.append(c);
}

QString ClassAnalyzer::parseClassName(const QString& classDeclaration)
{
  QStringList tokens = classDeclaration.split(' ', QString::SkipEmptyParts);

  if (tokens.isEmpty())
  {
    return QString();
  }

  if (tokens.last().isEmpty())
  {
    return QString();
  }

  return tokens.last();
}

QStringList ClassAnalyzer::parseBaseClassNames(const QString& baseClasses)
{
  QStringList baseClassNames;

  QStringList tokens = baseClasses.split(',', QString::SkipEmptyParts);

  for (auto it = tokens.begin(); it != tokens.end(); it++)
  {
    QString baseClassName = parseClassName(*it);

    if (!baseClassName.isEmpty())
    {
      baseClassNames.append(baseClassName);
    }
  }

  return baseClassNames;
}

void ClassAnalyzer::parseNamespaces(const QString& code)
{
  m_namespaces.clear();

  QVector<int> namespacePositions = positions(code, "\\snamespace\\s", true);
  QVector<int> openingCurlyBracketPositions = positions(code, "{");
  QVector<int> closingCurlyBracketPositions = positions(code, "}");

  if (openingCurlyBracketPositions.size() != closingCurlyBracketPositions.size())
  {
    qDebug() << m_currentFile;
    qDebug() << "quantity of opening and closing curly brackets does not match";
    qDebug() << "quantity of opening curly brackets:" << openingCurlyBracketPositions.size();
    qDebug() << "quantity of closing curly brackets:" << closingCurlyBracketPositions.size();
    return;
  }

  QVector<int> allCurlyBracketPositions = openingCurlyBracketPositions;
  allCurlyBracketPositions.append(closingCurlyBracketPositions);

  qSort(allCurlyBracketPositions);

  QMap<int, int> curlyBracketPairs;
  for (int i = 0; i < allCurlyBracketPositions.size(); i++)
  {
    if (openingCurlyBracketPositions.contains(allCurlyBracketPositions[i]))
    {
      int nesting = 1;
      for (int j = i + 1; j < allCurlyBracketPositions.size(); j++)
      {
        if (openingCurlyBracketPositions.contains(allCurlyBracketPositions[j]))
        {
          nesting++;
        }
        else
        {
          nesting--;
        }

        if (nesting == 0)
        {
          curlyBracketPairs[allCurlyBracketPositions[i]] = allCurlyBracketPositions[j];
          break;
        }
      }
    }
  }

  //qDebug() << curlyBracketPairs;

  for (auto it = namespacePositions.begin(); it != namespacePositions.end(); it++)
  {
    Namespace ns;

    for (auto it2 = curlyBracketPairs.begin(); it2 != curlyBracketPairs.end(); it2++)
    {
      if (it2.key() > *it)
      {
        ns.setStartPosition(it2.key());
        ns.setStopPosition(it2.value());
        ns.setName(namespaceName(code, *it, it2.key()));
        m_namespaces.append(ns);
        break;
      }
    }
  }
}

QString ClassAnalyzer::getNamespacePrefix(int position)
{
  QString namespacePrefix;

  for (auto it = m_namespaces.begin(); it != m_namespaces.end(); it++)
  {
    if (position > it->startPosition() && position < it->stopPosition())
    {
      namespacePrefix.append(it->name());
      namespacePrefix.append("::");
    }
  }

  return namespacePrefix;
}

QVector<int> ClassAnalyzer::positions(const QString& code, const QString& token, bool isRegExp)
{
  QVector<int> positions;

  int position = -1;

  if (isRegExp)
  {
    position = code.indexOf(QRegExp(token));
  }
  else
  {
    position = code.indexOf(token);
  }

  while (position > -1)
  {
    positions.append(position);

    position++;

    if (isRegExp)
    {
      position = code.indexOf(QRegExp(token), position);
    }
    else
    {
      position = code.indexOf(token, position);
    }
  }

  return positions;
}

QString ClassAnalyzer::namespaceName(const QString& code, int startPos, int stopPos)
{
  return code.mid(startPos, stopPos - startPos).simplified().split(" ").last();
}

void ClassAnalyzer::postProcessBaseClasses()
{
  // append namespace prefixes if needed
  for (auto it = m_classes.begin(); it != m_classes.end(); it++)
  {
    if (!it->baseClasses().isEmpty())
    {
      QStringList baseClasses = it->baseClasses();

      for (auto it2 = baseClasses.begin(); it2 != baseClasses.end(); it2++)
      {
        QStringList splittedBaseClassName = it2->split("::");

        for (auto it3 = m_classes.begin(); it3 != m_classes.end(); it3++)
        {
          QStringList splittedClassName = it3->name().split("::");

          // check from back to front
          if (splittedClassName.last() == splittedBaseClassName.last())
          {
            QString fullName = splittedClassName.last();
            splittedClassName.removeLast();

            QStringList splitted = it->name().split("::");

            while(!splitted.isEmpty())
            {
              splitted.removeLast();

              if (splittedClassName == splitted)
              {
                for (auto it4 = splitted.rbegin(); it4 != splitted.rend(); it4++)
                {
                  fullName.prepend("::");
                  fullName.prepend(*it4);
                }

                break;
              }
            }

            *it2 = fullName;
          }
        }
      }

      it->setBaseClasses(baseClasses);
    }
  }
}

void ClassAnalyzer::printAllClasses()
{
  for (auto it = m_classes.begin(); it != m_classes.end(); it++)
  {
    qDebug() << it->header() << it->name() << it->baseClasses();
  }

  qDebug() << "found" << m_classes.size() << "classes";
}

void ClassAnalyzer::printFilesWithMoreThanOneClassDeclaration()
{
  QList<unsigned int> keys = m_numberOfClassesPerFile.keys();

  for (auto it = keys.rbegin(); it != keys.rend(); it++)
  {
    if (*it > 1)
    {
      QStringList headers = m_numberOfClassesPerFile.values(*it);

      for (auto it2 = headers.begin(); it2 != headers.end(); it2++)
      {
        qDebug() << *it << "classes defined in " << *it2;
      }
    }
  }
}
