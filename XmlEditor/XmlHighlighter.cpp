#include <QDebug>

#include "XmlHighlighter.h"
#include "QColorEx.h"
#include "XmlParser.h"

XmlHighlighter::XmlHighlighter(QTextDocument *parent) :
  QSyntaxHighlighter(parent),
  m_commentStartExpression(QRegExp("<!--")),
  m_commentEndExpression(QRegExp("-->"))
{
  m_xmlParser = new XmlParser();
  init();
}

XmlHighlighter::~XmlHighlighter()
{
  delete m_xmlParser;
}


void XmlHighlighter::init()
{

}

void XmlHighlighter::highlightBlock(const QString &text)
{
  m_xmlParser->parse(text);
  QList<QPair<int, int>> tagPositions = m_xmlParser->tagPositions();
  QList<QPair<int, int>> attributeValuePositions = m_xmlParser->attributeValuePositions();
  QList<QPair<int, int>> attributeNamePositions = m_xmlParser->attributeNamePositions();

  QTextCharFormat textCharFormat;
  textCharFormat.setForeground(Qt::blue);

  for (auto it : tagPositions)
  {
    setFormat(it.first, it.second - it.first + 1, textCharFormat);
  }

  textCharFormat.setForeground(Qt::red);
  for (auto it : attributeValuePositions)
  {
    setFormat(it.first, it.second - it.first + 1, textCharFormat);
  }

  textCharFormat.setForeground(Qt::gray);
  for (auto it : attributeNamePositions)
  {
    setFormat(it.first, it.second - it.first, textCharFormat);
  }

  // mark comments

  textCharFormat.setForeground(Qt::green);

  setCurrentBlockState(0);

  int startIndex = 0;
  if (previousBlockState() != 1)
  {
    startIndex = m_commentStartExpression.indexIn(text);
  }

  while (startIndex >= 0)
  {
    int endIndex = m_commentEndExpression.indexIn(text, startIndex);
    int commentLength;
    if (endIndex == -1)
    {
      setCurrentBlockState(1);
      commentLength = text.length() - startIndex;
    }
    else
    {
      commentLength = endIndex - startIndex + m_commentEndExpression.matchedLength();
    }
    setFormat(startIndex, commentLength, textCharFormat);
    startIndex = m_commentStartExpression.indexIn(text, startIndex + commentLength);
  }
}
