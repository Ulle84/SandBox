#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

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
  void on_pushButton_clicked();

private:
  Ui::MainWindow* ui;
  void parseTree(QList<QAction*>, QTreeWidgetItem* parent);
};

#endif // MAINWINDOW_H
