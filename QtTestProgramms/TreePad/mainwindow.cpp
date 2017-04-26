/*
Editing of tree should be done in explorer

ToDo
- set directory dynamically
- save function for text-edit
- define file encoding (UTF-8)
- differnece between folder and file
- add folder
- add file
- set shortcut for save

Ideas
- search in tree
- search in files

Done
- collapse whole tree
- expand whole tree
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionSave->setShortcuts(QKeySequence::Save);

    dir = QDir("E:/temp/2013-06-25_16-52h_TreePadTest");
    parseFileTree(dir, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::parseFileTree(QDir dir, QTreeWidgetItem* parent)
{
    for (int i = 0; i < dir.entryList().length(); i++)
    {
        QString label = dir.entryList().at(i);
        if (label != ".." && label != ".")
        {
            QTreeWidgetItem *treeWidgetItem;
            if (parent == 0)
            {
                // top level tree item
                treeWidgetItem = new QTreeWidgetItem(ui->treeWidget);
            }
            else
            {
                treeWidgetItem = new QTreeWidgetItem(parent);
            }
            treeWidgetItem->setText(0, label);
            parseFileTree(QDir(dir.absolutePath() + "/" + label), treeWidgetItem);
        }
    }
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    showText(item, column);
}

void MainWindow::on_treeWidget_itemActivated(QTreeWidgetItem *item, int column)
{
    showText(item, column);
}

void MainWindow::on_treeWidget_itemEntered(QTreeWidgetItem *item, int column)
{
    showText(item, column);
}

void MainWindow::showText(QTreeWidgetItem *item, int column)
{
    if (!item->text(column).contains("."))
    {
        // do not change anything, sinc this is a folder, not a document
        return;
    }

    ui->plainTextEdit->clear();

    // generate fileName and show in label
    fileName = item->text(column);
    while(item->parent())
    {
        item = item->parent();
        fileName.prepend("/");
        fileName.prepend(item->text(column));
    }
    fileName.prepend("/");
    fileName.prepend(dir.absolutePath());
    ui->statusBar->showMessage(fileName);

    // open file and show content
    QFile file (fileName);
    if (file.open(QIODevice::ReadWrite))
    {
        ui->plainTextEdit->setPlainText(file.readAll());
    }
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);
    out << ui->plainTextEdit->toPlainText();

    file.close();
}

void MainWindow::on_actionCollapse_All_triggered()
{
    ui->treeWidget->collapseAll();
}

void MainWindow::on_actionExpand_All_triggered()
{
    ui->treeWidget->expandAll();
}

void MainWindow::on_actionShow_in_HTML_Viewer_triggered(bool checked)
{

}
