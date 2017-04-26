#include "Widget.h"
#include "ui_Widget.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QMessageBox>
#include <QProcessEnvironment>
#include <QStringList>

#include <iostream>

Widget::Widget(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
  ui->lineEditPath->setText(QDir::currentPath());

  QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
#ifdef Q_WS_WIN
  ui->lineEditCreator->setText(env.value("username"));
#else
  ui->lineEditCreator->setText(env.value("user"));
#endif
}

Widget::~Widget()
{
  delete ui;
}

void Widget::on_pushButtonCreateClass_clicked()
{
  if (!QDir(ui->lineEditPath->text()).isReadable())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("%1 is not valid").arg(ui->labelPath->text()));
    messageBox.exec();
    return;
  }

  if (ui->lineEditClassName->text().length() == 0)
  {
    QMessageBox messageBox;
    messageBox.setText(tr("Content of %1 is emtpy").arg(ui->labelClassName->text()));
    messageBox.exec();
    return;
  }

  writeFile("h", createContentHeader());
  writeFile("cpp", createContentImplementation());
}

QString Widget::createContentHeader()
{
  return QString("/*******************************************************************************\n" \
                 "File             : $RCSfile:$\n" \
                 "Creator          : %1\n" \
                 "Date of Creation : %4\n" \
                 "Project          : %2\n\n" \
                 "Last Change\n" \
                 "  $Author:$\n" \
                 "  $Date:$\n" \
                 "  $Revision:$\n" \
                 "*******************************************************************************/\n\n" \
                 "#pragma once\n\n" \
                 "class %3\n" \
                 "{\n" \
                 "public:\n" \
                 "\t%3();\n" \
                 "\t~%3();\n" \
                 "};\n\n" \
                 "/*******************************************************************************\n" \
                 "Last changes\n\n" \
                 "$Log:$\n" \
                 "*******************************************************************************/").arg(ui->lineEditCreator->text()).arg(ui->lineEditProject->text()).arg(ui->lineEditClassName->text()).arg(QDate::currentDate().toString("yyyy-MM-dd"));
}

QString Widget::createContentImplementation()
{
  return QString("/*******************************************************************************\n" \
                 "File             : $RCSfile:$\n" \
                 "Creator          : %1\n" \
                 "Date of Creation : %4\n" \
                 "Project          : %2\n\n" \
                 "Last Change\n" \
                 "  $Author:$\n" \
                 "  $Date:$\n" \
                 "  $Revision:$\n" \
                 "*******************************************************************************/\n\n" \
                 "#include \"%3.h\"\n\n" \
                 "%3::%3()\n" \
                 "{\n\n" \
                 "}\n\n" \
                 "%3::~%3()\n" \
                 "{\n\n" \
                 "}\n\n" \
                 "/*******************************************************************************\n" \
                 "Last changes\n\n" \
                 "$Log:$\n" \
                 "*******************************************************************************/").arg(ui->lineEditCreator->text()).arg(ui->lineEditProject->text()).arg(ui->lineEditClassName->text()).arg(QDate::currentDate().toString("yyyy-MM-dd"));
}

void Widget::writeFile(QString fileExtension, QString fileContent)
{
  QFile file(QString("%1.%4").arg(getFilePathWithoutExtension()).arg(fileExtension));

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    return;
  }

  QTextStream out(&file);
  out << fileContent;

  file.close();
}

QString Widget::getFilePathWithoutExtension()
{
  return QString("%1%2%3").arg(ui->lineEditPath->text()).arg(QDir::separator()).arg(ui->lineEditClassName->text());
}
