#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDir>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void parseFileTree(QDir dir, QTreeWidgetItem *parent);
    
private slots:
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void on_treeWidget_itemActivated(QTreeWidgetItem *item, int column);
    void on_treeWidget_itemEntered(QTreeWidgetItem *item, int column);
    void on_actionSave_triggered();
    void on_actionCollapse_All_triggered();
    void on_actionExpand_All_triggered();

    void on_actionShow_in_HTML_Viewer_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    QDir dir;
    void showText(QTreeWidgetItem *item, int column);
    QString fileName;
};

#endif // MAINWINDOW_H
