#include "DoubleButton.h"
#include "ui_DoubleButton.h"

#include <QMessageBox>

DoubleButton::DoubleButton(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::DoubleButton)
{
  ui->setupUi(this);
  m_test << "uno" << "dos" << "tres";
}

DoubleButton::~DoubleButton()
{
  delete ui;
}

QString DoubleButton::buttonText1()
{
  return ui->pushButton1->text();
}

QString DoubleButton::buttonText2()
{
  return ui->pushButton2->text();
}

void DoubleButton::setButtonText1(const QString& buttonText1)
{
  ui->pushButton1->setText(buttonText1);
}

void DoubleButton::setButtonText2(const QString& buttonText2)
{
  ui->pushButton2->setText(buttonText2);
}

void DoubleButton::on_pushButton1_clicked()
{
  QMessageBox messageBox;
  messageBox.setText("button 1 clicked");
  messageBox.exec();
}

void DoubleButton::on_pushButton2_clicked()
{
  QMessageBox messageBox;
  messageBox.setText("button 2 clicked");
  messageBox.exec();
}
