// http://doc.qt.io/qt-4.8/designer-using-a-ui-file.html

#include <QUiLoader>
#include <QFile>
#include <QMessageBox>
#include <QPushButton>
#include <QPlainTextEdit>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QUiLoader loader;

  /*QFile file(":/forms/Form.ui");
  file.open(QFile::ReadOnly);
  QWidget *myWidget = loader.load(&file, this);
  file.close();
  ui->verticalLayout->addWidget(myWidget);*/

  QFile file2(":/forms/AlternativeForm.ui");
  file2.open(QFile::ReadOnly);
  QWidget *myWidget2 = loader.load(&file2, this);
  file2.close();
  ui->verticalLayout->addWidget(myWidget2);

  QMetaObject::connectSlotsByName(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::appendText(const QString &text)
{
  QPlainTextEdit* plainTextEdit = findChild<QPlainTextEdit*>("plainTextEdit");
  if (plainTextEdit)
  {
    plainTextEdit->appendPlainText(text);
  }
}

void MainWindow::on_pushButton1_clicked()
{
  appendText("pushButton1 clicked");
}

void MainWindow::on_pushButton2_clicked()
{
  appendText("pushButton2 clicked");
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    // TODO load selected ui file
}
