#ifndef SEARCHABLETEXTEDIT_H
#define SEARCHABLETEXTEDIT_H

#include <QWidget>

namespace Ui {
class SearchableTextEdit;
}

class SearchableTextEdit : public QWidget
{
  Q_OBJECT

public:
  explicit SearchableTextEdit(QWidget *parent = 0);
  ~SearchableTextEdit();

  void setText(const QString& text);
  QString text();

  void setResultsVisible(bool visible);

  void doSearch(const QString& searchText, bool caseSenstive);
  void resetSearch();

private slots:
  void on_pushButtonPrevious_clicked();
  void on_pushButtonNext_clicked();

private:
  void updateResultLabel(int index);
  void markNextSearchResult();
  void markPreviousSearchResult();
  void markSearchResult(int index);

  Ui::SearchableTextEdit *ui;

  QList<int> m_startPositions;

  QString m_searchText;
};

#endif // SEARCHABLETEXTEDIT_H
