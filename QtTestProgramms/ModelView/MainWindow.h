#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QItemSelection;
class QStandardItem;
class QTreeView;

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void selectionChangedSlot(const QItemSelection & newSelection, const QItemSelection & oldSelection);

private:
  void example1();
  void example2();
  void example3();

  QList<QStandardItem *> prepareRow(const QString &first, const QString &second, const QString &third);

  Ui::MainWindow *ui;
  QTreeView* m_treeView;
};

#endif // MAINWINDOW_H
