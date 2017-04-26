#include <QDebug>

#include "DecoratorExample.h"
#include "ui_DecoratorExample.h"
#include "Component.h"
#include "Decorator.h"
#include "DecoratorA.h"
#include "DecoratorB.h"

DecoratorExample::DecoratorExample(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DecoratorExample)
{
  ui->setupUi(this);

  mComponent = new Component();
  mDecorator = new DecoratorA(mComponent);
  mDoubleDecorator = new DecoratorB(mDecorator);
}

DecoratorExample::~DecoratorExample()
{
  delete mDoubleDecorator;
  delete mDecorator;
  delete mComponent;
  delete ui;
}

void DecoratorExample::on_pushButtonOperateComponent_clicked()
{
    qDebug() << "subject operation: " + QString::number(mComponent->operation());
}

void DecoratorExample::on_pushButtonOperateDecorator_clicked()
{
    qDebug() << "decorator operation: " + QString::number(mDecorator->operation());
}

void DecoratorExample::on_pushButtonOperateDoubleDecorator_clicked()
{
    qDebug() << "double decorator operation: " + QString::number(mDoubleDecorator->operation());
}
