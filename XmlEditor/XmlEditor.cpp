#include <QKeyEvent>

#include "XmlEditor.h"
#include "XmlHighlighter.h"

XmlEditor::XmlEditor(QWidget *parent) :
  QTextEdit(parent)
{
  m_highlighter = new XmlHighlighter(document());

  connect(this, &XmlEditor::textChanged, this, &XmlEditor::onTextChanged);
  connect(this, &XmlEditor::cursorPositionChanged, this, &XmlEditor::onCursorPositionChanged);
}

XmlEditor::~XmlEditor()
{
  delete m_highlighter;
}

void XmlEditor::keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_Tab)
  {
    QTextCursor cursor = textCursor();
    cursor.insertText("  ");
    setTextCursor(cursor);
    return;
  }

  if (e->key() == Qt::Key_Return)
  {
    // TODO check indentation
    QTextCursor cursor = textCursor();
    cursor.insertText("\n");
    setTextCursor(cursor);
    return;
  }

  QString string;

  if (e->key() == '\'')
  {
    string = "\'\'";
  }
  else if (e->key() == '\"')
  {
    string = "\"\"";
  }
  else if (e->key() == '(')
  {
    string = "()";

  }
  else if (e->text() == "[")
  {
    string = "[]";
  }
  else if (e->text() == "{")
  {
    string = "{}";
  }

  if (string.isEmpty())
  {
    QTextEdit::keyPressEvent(e);
  }
  else
  {
    QTextCursor cursor = textCursor();
    cursor.insertText(string);
    cursor.movePosition(QTextCursor::PreviousCharacter);
    setTextCursor(cursor);
  }
}

void XmlEditor::onTextChanged()
{

}

void XmlEditor::onCursorPositionChanged()
{

}
