#include <QDebug>

#include "SearchableTextEdit.h"
#include "ui_SearchableTextEdit.h"

SearchableTextEdit::SearchableTextEdit(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SearchableTextEdit)
{
  ui->setupUi(this);
  ui->results->setVisible(false);
}

SearchableTextEdit::~SearchableTextEdit()
{
  delete ui;
}

void SearchableTextEdit::setText(const QString &text)
{
  ui->textEditInput->setPlainText(text);
}

QString SearchableTextEdit::text()
{
  return ui->textEditInput->toPlainText();
}

void SearchableTextEdit::setResultsVisible(bool visible)
{
  ui->results->setVisible(visible);
}

void SearchableTextEdit::doSearch(const QString &searchText, bool caseSenstive)
{
  m_searchText = searchText;

  //ui->results->setVisible(!m_searchText.isEmpty());

  QTextDocument *document = ui->textEditInput->document();

  // TODO is this correct?
  document->undo();

  m_startPositions.clear();

  if (m_searchText.isEmpty())
  {
    updateResultLabel(-1);
    return;
  }

  QTextCursor highlightCursor(document);
  QTextCursor cursor(document);

  cursor.beginEditBlock();

  QTextCharFormat plainFormat(highlightCursor.charFormat());
  QTextCharFormat colorFormat = plainFormat;
  colorFormat.setForeground(Qt::red);

  while (!highlightCursor.isNull() && !highlightCursor.atEnd())
  {
    highlightCursor = document->find(m_searchText, highlightCursor, caseSenstive ? QTextDocument::FindCaseSensitively : QTextDocument::FindFlags());

    if (!highlightCursor.isNull())
    {
      highlightCursor.mergeCharFormat(colorFormat);
      m_startPositions.append(highlightCursor.position() - m_searchText.length());
    }
  }

  cursor.endEditBlock();

  if (!m_startPositions.isEmpty())
  {
    markSearchResult(0);
  }
  else
  {
    updateResultLabel(-1);
  }




  //ui->results->setVisible(!m_startPositions.isEmpty());

}

void SearchableTextEdit::resetSearch()
{
  QTextDocument *document = ui->textEditInput->document();

  // TODO is this correct?
  document->undo();

  ui->results->setVisible(false);
}


void SearchableTextEdit::on_pushButtonPrevious_clicked()
{
  markPreviousSearchResult();
}

void SearchableTextEdit::on_pushButtonNext_clicked()
{
  markNextSearchResult();
}

void SearchableTextEdit::updateResultLabel(int index)
{
  // TODO label should always have the same with - so no controls are "jumping"
  ui->labelIndex->setText(QString("%1 / %2").arg(index + 1).arg(m_startPositions.length()));
}

void SearchableTextEdit::markNextSearchResult()
{
  int currentPosition = ui->textEditInput->textCursor().position();

  for (int i = 0; i < m_startPositions.length(); ++i)
  {
    if (m_startPositions[i] > currentPosition)
    {
      markSearchResult(i);
      return;
    }
  }

  markSearchResult(0);
}

void SearchableTextEdit::markPreviousSearchResult()
{
  int currentPosition = ui->textEditInput->textCursor().position();

  int stringLength = m_searchText.length();

  for (int i = m_startPositions.length() - 1; i >= 0; --i)
  {
    if (m_startPositions[i] + stringLength < currentPosition)
    {
      markSearchResult(i);
      return;
    }
  }

  markSearchResult(m_startPositions.length() - 1);
}

void SearchableTextEdit::markSearchResult(int index)
{
  if (index < 0)
  {
    index = 0;
  }

  if (index >= m_startPositions.length())
  {
    index = m_startPositions.length() - 1;
  }

  QTextCursor c = ui->textEditInput->textCursor();
  c.setPosition(m_startPositions.at(index));
  c.setPosition(m_startPositions.at(index) + m_searchText.length(), QTextCursor::KeepAnchor);
  ui->textEditInput->setTextCursor(c);

  updateResultLabel(index);
}

