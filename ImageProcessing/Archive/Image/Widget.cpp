#include <QByteArray>
#include <QDebug>

#include "Widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
  test();
}

Widget::~Widget()
{
  delete ui;
}

void Widget::test()
{
  QByteArray ba(10, 0);

  qDebug() << ba.size();

  for (int i = 0; i < ba.size(); i++)
  {
    qDebug() << (int) ba.at(i);
  }
}
