#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

private slots:
  void on_pushButtonClearList_clicked();

  void on_pushButtonSelectFiles_clicked();

  void on_pushButtonDeleteEvaluationData_clicked();

private:
  Ui::MainWindow* ui;
  QString lastSelectedDir;
  void setLastSelectedDir(QString fileName);
};

#endif // MAINWINDOW_H
