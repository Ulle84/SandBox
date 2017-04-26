#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QPoint>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox messageBox;
    int xRel = ui->pushButton->x();
    int yRel = ui->pushButton->y();
    QPoint rel;
    rel.setX(xRel);
    rel.setY(yRel);
    QPoint abs = ui->pushButton->mapToGlobal(rel);
    int xAbs = abs.x();
    int yAbs = abs.y();
    messageBox.setText(tr("xRel: %1, yRel: %2\nxAbs: %3, yAbs: %4").arg(xRel).arg(yRel).arg(xAbs).arg(yAbs));
    messageBox.exec();
}
