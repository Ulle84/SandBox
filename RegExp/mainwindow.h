#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDomDocument>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void resizeTable();
    void clearList();
    void processFileList();
    void setLastSelectedDir(QString fileName);

private slots:
    void on_pushButtonSelectFiles_clicked();
    void on_pushButtonAppendLine_clicked();
    void on_pushButtonClearTable_clicked();
    void on_pushButtonSearchAndReplace_clicked();
    void on_pushButtonClearFileList_clicked();
    void on_pushButtonResizeTable_clicked();
    void on_pushButtonSaveTable_clicked();

    void on_pushButtonLoadTable_clicked();

private:
    Ui::MainWindow *ui;
    QString lastSelectedDir;
    QDomDocument domDocument;
};

#endif // MAINWINDOW_H
