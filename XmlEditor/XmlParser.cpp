#include "XmlParser.h"

XmlParser::XmlParser()
{

}

void XmlParser::parse(const QString &xml)
{
  m_tagPositions.clear();
  m_attributeValuePositions.clear();
  m_attributeNamePositions.clear();

  int xmlLength = xml.length();

  State state = State::Text;

  int beginPosTag = 0;
  int beginPosAttributeValue = 0;
  int beginPosAttributeName = 0;

  for (int i = 0; i < xmlLength; ++i)
  {
    if (state == State::Text)
    {
      if (xml[i] == '<')
      {
        beginPosTag = i;
        state = State::InsideTag;
        continue;
      }
    }
    else if (state == State::InsideTag)
    {
      if (xml[i] == '>')
      {
        m_tagPositions.append(qMakePair(beginPosTag, i));
        state = State::Text;
        continue;
      }
      else if (xml[i] == '\"')
      {
        beginPosAttributeValue = i;
        state = State::InsideAttributeValue;
        continue;
      }
      else if (xml[i] == ' ')
      {
        beginPosAttributeName = i;
        state = State::InsideAttributeName;
        continue;
      }
    }
    else if (state == State::InsideAttributeName)
    {
      if (xml[i] == '=')
      {
        m_attributeNamePositions.append(qMakePair(beginPosAttributeName, i));
        state = State::InsideTag;
        continue;
      }
    }
    else if (state == State::InsideAttributeValue)
    {
      if (xml[i] == '\"')
      {
        m_attributeValuePositions.append(qMakePair(beginPosAttributeValue, i));
        state = State::InsideTag;
        continue;
      }
    }



  }
}

QList<QPair<int, int> > XmlParser::tagPositions()
{
  return m_tagPositions;
}

QList<QPair<int, int> > XmlParser::attributeValuePositions()
{
  return m_attributeValuePositions;
}

QList<QPair<int, int> > XmlParser::attributeNamePositions()
{
  return m_attributeNamePositions;
}
