#ifndef XMLEDITOR_H
#define XMLEDITOR_H

#include <QTextEdit>

class XmlHighlighter;
class XmlParser;


class XmlEditor : public QTextEdit
{
  Q_OBJECT

public:
  explicit XmlEditor(QWidget *parent = 0);
  ~XmlEditor();

protected:
  void keyPressEvent(QKeyEvent *e) override;

private slots:
  void onTextChanged();
  void onCursorPositionChanged();

private:
  XmlHighlighter* m_highlighter;
};

#endif // XMLEDITOR_H
