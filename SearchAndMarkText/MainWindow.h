#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

class SearchableTextEdit;

class QSettings;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_lineEditSearch_textChanged(const QString& searchString);

  void on_actionFind_triggered();

  void on_checkBoxCaseSensitive_stateChanged(int arg1);

  void on_pushButtonClose_clicked();

private:
  void doSearch();
  void resetSearch();

  Ui::MainWindow *ui;
  QSettings* m_settings;

  QList<SearchableTextEdit*> m_textEdits;
};

#endif // MAINWINDOW_H
