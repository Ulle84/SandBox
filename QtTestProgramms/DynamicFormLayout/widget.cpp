#include"widget.h"
#include"ui_widget.h"

#include <QDoubleValidator>
#include <QIntValidator>

#include <QCheckBox>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QStringList>

Widget::Widget(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
  constFormLayoutLines = ui->formLayout->rowCount();

  QStringList controlNames;
  controlNames.append("CheckBox");
  controlNames.append("LineEdit");
  controlNames.append("ComboBox");
  controlNames.append("PlainTextEdit");
  controlNames.append("SpinBox");
  controlNames.append("DoubleSpinBox");
  controlNames.sort();

  ui->comboBox->addItems(controlNames);
}

Widget::~Widget()
{
  delete ui;
}

void Widget::on_comboBox_currentIndexChanged(const QString& string)
{
  // delete old elements - Attention: Bug in formLayout class -> rowCount is not decremented when takeAt() is used
  while (QLayoutItem* item = ui->formLayout->takeAt(constFormLayoutLines * 2))
  {
    delete item->widget();
    delete item;
  }

  // neue sachen anhängen
  if (string == "CheckBox")
  {
    QCheckBox* checkBox = new QCheckBox();
    ui->formLayout->addRow("default", checkBox);
    return;
  }

  if (string == "LineEdit")
  {
    QLineEdit* lineEdit = new QLineEdit();
    ui->formLayout->addRow("default", lineEdit);
    return;
  }

  if (string == "ComboBox")
  {
    QLineEdit* lineEdit = new QLineEdit();
    ui->formLayout->addRow("default option", lineEdit);

    QPlainTextEdit* plainTextEdit = new QPlainTextEdit();
    ui->formLayout->addRow("other options", plainTextEdit);
    return;
  }

  if (string == "PlainTextEdit")
  {
    QPlainTextEdit* plainTextEdit = new QPlainTextEdit();
    ui->formLayout->addRow("default", plainTextEdit);
    return;
  }

  if (string == "SpinBox")
  {
    QIntValidator* intValidator = new QIntValidator();

    QLineEdit* lineEdit = new QLineEdit("10");
    lineEdit->setValidator(intValidator);
    ui->formLayout->addRow("default", lineEdit);

    QLineEdit* lineEditMin = new QLineEdit("0");
    lineEditMin->setValidator(intValidator);
    ui->formLayout->addRow("minimum", lineEditMin);

    QLineEdit* lineEditMax = new QLineEdit("100");
    lineEditMax->setValidator(intValidator);
    ui->formLayout->addRow("maximum", lineEditMax);
    return;
  }

  if (string == "DoubleSpinBox")
  {
    QDoubleValidator* doubleValidator = new QDoubleValidator();

    QLineEdit* lineEdit = new QLineEdit("10.000");
    lineEdit->setValidator(doubleValidator);
    ui->formLayout->addRow("default", lineEdit);

    QLineEdit* lineEditMin = new QLineEdit("0.000");
    lineEditMin->setValidator(doubleValidator);
    ui->formLayout->addRow("minimum", lineEditMin);

    QLineEdit* lineEditMax = new QLineEdit("100.000");
    lineEditMax->setValidator(doubleValidator);
    ui->formLayout->addRow("maximum", lineEditMax);

    QSpinBox* spinBox = new QSpinBox();
    spinBox->setMinimum(0);
    spinBox->setMaximum(10);
    spinBox->setValue(3);
    ui->formLayout->addRow("precision", spinBox);
    return;
  }
}
