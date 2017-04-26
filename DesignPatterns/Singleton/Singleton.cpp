#include "Singleton.h"
#include "ui_Singleton.h"
#include "SingletonEager.h"

Singleton::Singleton(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Singleton)
{
  ui->setupUi(this);
}

Singleton::~Singleton()
{
  delete ui;
}

void Singleton::on_pushButtonAccessSingleton_clicked()
{
  ui->plainTextEdit->appendPlainText(SingletonEager::getInstance()->sayHello());
}
