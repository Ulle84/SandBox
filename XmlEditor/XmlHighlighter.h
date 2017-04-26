#ifndef XMLHIGHLIGHTER_H
#define XMLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class QTextDocument;

class XmlParser;

class XmlHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT

public:
  XmlHighlighter(QTextDocument* parent = 0);
  ~XmlHighlighter();

protected:
  void highlightBlock(const QString &text) override;

private:
  void init();

  QRegExp m_commentStartExpression;
  QRegExp m_commentEndExpression;

  XmlParser* m_xmlParser;
};

#endif
