#include "Widget.h"
#include "ui_Widget.h"

#include <QString>
#include <QUrl>
#include <QPrinter>
#include <QPrintDialog>
#include <QWebFrame>
#include <QDir>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
  ui->setupUi(this);
  print();
}

Widget::~Widget()
{
  delete ui;
}

void Widget::print()
{
  QDir dir("D:\\test.html");
  ui->webView->load(QUrl::fromLocalFile(dir.absolutePath()));
}

void Widget::on_webView_loadFinished(bool loadFinished)
{
  qDebug() << "load finished";

  QPrinter printer(QPrinter::HighResolution);
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setPageSize(QPrinter::A4);
  printer.setPageMargins(10, 10, 10, 10, QPrinter::Millimeter);
  printer.setColorMode(QPrinter::GrayScale);
  printer.setOutputFileName("D:\\test.pdf");
  ui->webView->page()->mainFrame()->print(&printer);
}
