#include "Widget.h"
#include "ui_Widget.h"

#include <QString>
#include <QtXml>
#include <QtXmlPatterns>
#include <QUrl>
#include <QPrinter>
#include <QPrintDialog>
#include <QWebFrame>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    convertToHtml();
    print();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::convertToHtml()
{
    QString out;
    QXmlQuery query(QXmlQuery::XSLT20);
    query.setFocus(QUrl::fromLocalFile("D:/Sandboxes/ViAcquiGenICam/ViAcquiGenICam/config/ViAcquiGenICam_default.xml"));
    query.setQuery(QUrl::fromLocalFile("D:/Sandboxes/ViAcquiDocumentation/ViAcquiDocumentation/ViParameterFileDocumentationV2.xsl"));
    query.evaluateTo(&out);
    ui->webView->setHtml(out);
    ui->plainTextEdit->setPlainText(out);
}

void Widget::print()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPrinter::A4);
    printer.setPageMargins(10, 10, 10, 10, QPrinter::Millimeter);
    printer.setColorMode(QPrinter::Color);
    printer.setOutputFileName("C:\\test.pdf");
    ui->webView->page()->mainFrame()->print(&printer);
}
