#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QString>
#include <QPair>
#include <QList>

class XmlParser
{
public:
  XmlParser();

  void parse(const QString& xml);
  QList<QPair<int, int>> tagPositions();
  QList<QPair<int, int>> attributeValuePositions();
  QList<QPair<int, int>> attributeNamePositions();

private:
  enum class State
  {
    Text,
    InsideTag,
    InsideAttributeName,
    InsideAttributeValue
  };

  QList<QPair<int, int>> m_tagPositions;
  QList<QPair<int, int>> m_attributeValuePositions;
  QList<QPair<int, int>> m_attributeNamePositions;
};

#endif // XMLPARSER_H
