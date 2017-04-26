#ifndef CLASSANALYZER_H
#define CLASSANALYZER_H

#include <QMap>
#include <QList>
#include <QString>
#include <QPair>
#include <QStringList>
#include <QMultiMap>

#include "Class.h"
#include "Namespace.h"

class ClassAnalyzer
{
public:
  ClassAnalyzer();
  ~ClassAnalyzer();

  void parseFolder(const QString& folder);
  void parseFolders(const QStringList& folders);

private:
  void removeComments(QString& code);
  void removeSequences(QString& code, const QString& startTag, const QString& endTag, bool removeEndTag = true);
  void parseFile(const QString& fileName);
  void parseClassDeclaration(const QString& classDeclaration, int position);
  QString parseClassName(const QString& classDeclaration);
  QStringList parseBaseClassNames(const QString& baseClasses);
  void parseNamespaces(const QString& code);
  QString getNamespacePrefix(int position);
  QVector<int> positions(const QString& code, const QString& token, bool isRegExp = false);
  QString namespaceName(const QString& code, int startPos, int stopPos);
  void postProcessBaseClasses();
  void printAllClasses();
  void printFilesWithMoreThanOneClassDeclaration();

  QList<Class> m_classes;
  QList<Namespace> m_namespaces;
  QString m_currentFile;
  QMultiMap<unsigned int, QString> m_numberOfClassesPerFile;
};

#endif // CLASSANALYZER_H
