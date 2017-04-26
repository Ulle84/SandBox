#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

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
  void on_checkBox_stateChanged(int arg1);

private:
  Ui::MainWindow* ui;
  QMenu* file;
  QMenu* service;
  QAction* FileSave;
  QAction* FileOpen;
  QAction* FileSaveAs;
  QAction* serviceEntry01;
  QList<QAction*> actionList;
};

#endif // MAINWINDOW_H
