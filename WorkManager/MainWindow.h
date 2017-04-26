#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>

class TreeModel;
class ProxyModel;
class QSettings;
class QAction;

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
  void on_lineEdit_textChanged(const QString& searchString);
  void on_actionAddChild_triggered();
  void on_actionAddSibling_triggered();
  void on_actionMoveUp_triggered();
  void on_actionMoveDown_triggered();
  void on_actionMoveLeft_triggered();
  void on_actionMoveRight_triggered();
  void on_actionDelete_triggered();

  void onTreeViewSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

  void on_pushButton_clicked();

private:
  void addNode(const QModelIndex& modelIndexParent);

  Ui::MainWindow* ui;

  TreeModel* m_treeModel;
  ProxyModel* m_proxyModel;
  QSettings* m_settings;
  QAction* m_actionNew;
};

#endif
