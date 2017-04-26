#include "Widget.h"
#include "ui_Widget.h"

#include <QStringList>

Widget::Widget(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
  QStringList diags;
  diags.append("diag1");
  diags.append("diag2");
  diags.append("diag3");

  /*
   *historyModel = new QStringListModel(this);
  historyModel->setStringList(*historyStringList);
   *historyListView->setModel(historyModel);

  historyListView->setAlternatingRowColors(true);*/

  ui->listView->setStyleSheet("alternate-background-color: darkgrey;");
  ui->listView->setAlternatingRowColors(true);
  stringListModel = new QStringListModel(this);
  stringListModel->setStringList(diags);
  ui->listView->setModel(stringListModel);

  diags.append("diag4");
  stringListModel->setStringList(diags);

}

Widget::~Widget()
{
  delete ui;
  delete stringListModel;
}
