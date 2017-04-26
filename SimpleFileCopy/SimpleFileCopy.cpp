#include "SimpleFileCopy.h"
#include "ui_SimpleFileCopy.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTime>

SimpleFileCopy::SimpleFileCopy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimpleFileCopy)
{
    ui->setupUi(this);
}

SimpleFileCopy::~SimpleFileCopy()
{
    delete ui;
}

void SimpleFileCopy::on_pushButtonCopy_clicked()
{
    QFile destination (ui->lineEditDestination->text());
    if (destination.exists())
    {
        if (!destination.remove())
        {
            setNewTextAtStatusBar(tr("old file could not be removed"));
            return;
        }

    }

    if (QFile::copy(ui->lineEditSource->text(), ui->lineEditDestination->text()))
    {
        setNewTextAtStatusBar(tr("file was copied sucessfully"));
    }
    else
    {
        setNewTextAtStatusBar(tr("file could not be copied"));
    }
}

void SimpleFileCopy::setTimeOnStatusBar()
{
    ui->labelTime->setText(QTime::currentTime().toString("hh:mm:ss"));
}

void SimpleFileCopy::setNewTextAtStatusBar(const QString& newText)
{
    setTimeOnStatusBar();
    ui->labelStatusContent->setText(newText);
}

void SimpleFileCopy::on_pushButtonSelectSource_clicked()
{
    QString source = QFileDialog::getOpenFileName();
    if (source.length() != 0)
    {
        ui->lineEditSource->setText(source);
    }
}

void SimpleFileCopy::on_pushButtonSelectDestination_clicked()
{
    QString destination = QFileDialog::getOpenFileName();
    if (destination.length() != 0)
    {
        ui->lineEditDestination->setText(destination);
    }
}
