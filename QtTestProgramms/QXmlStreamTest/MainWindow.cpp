#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFile>
#include <QString>
#include <QStringRef>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QXmlStreamAttributes>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonWriteXml_clicked()
{
    QFile file(ui->lineEditFilePath->text());

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.setAutoFormattingIndent(2);

    xml.writeStartDocument();
    xml.writeStartElement("ViAuthorisation");

    xml.writeTextElement("Text", QString("hello world"));
    xml.writeTextElement("Number", QString::number(0.987654321, 'f', 20));

    xml.writeStartElement("element");
    xml.writeAttribute("Attribute", "valueOfAttribute");
    xml.writeCharacters("valueOfText");
    xml.writeEndElement();

    xml.writeEmptyElement("onlyAttributeNotText");
    xml.writeAttribute("attribute", "valueOfAttribute");

    xml.writeEndElement();
    xml.writeEndDocument();

    file.close();
}

void MainWindow::on_pushButtonReadXml_clicked()
{
    QFile file(ui->lineEditFilePath->text());

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QXmlStreamReader xml(&file);

    if(!xml.readNextStartElement())
        return;

    if(xml.name() != "ViAuthorisation")
        return;

    while(xml.readNextStartElement())
    {
        if(xml.name() == "Text")
        {
            ui->plainTextEditOutput->appendPlainText("Text");
            ui->plainTextEditOutput->appendPlainText(xml.readElementText());
        }
        else if (xml.name() == "Number")
        {
            ui->plainTextEditOutput->appendPlainText("Number");
            double number = xml.readElementText().toDouble();
            ui->plainTextEditOutput->appendPlainText(QString::number(number, 'f', 20));
        }
        else if (xml.name() == "element")
        {
            ui->plainTextEditOutput->appendPlainText("element-attribute: ");
            QXmlStreamAttributes streamAttributes = xml.attributes();
            ui->plainTextEditOutput->appendPlainText(streamAttributes.value("Attribute").toString());
        }
    }
    file.close();
}
