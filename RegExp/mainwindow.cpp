/* ToDo
- new column: repeat - 0, 1, 2, 3, ... inf
- checkbox: clean unnesseary white space
- dropdown readmode: line by line, complete text
- edit + dropdown ident: tab, 1 space, 2 spaces, 3 spaces, 4 spaces,
- write documentation and short how-to
- delete selected line / selected cells
*/

/* nice to have
- drag and drop files from explorer on file-list
- replace buttons by menu-items, toolbar and context-menu
- splitter between list and table
- move table-rows up and down
*/

/* Done/History

2012-08-04 11:29 UBE - using RegExp -> use RegExp && true/false -> yes/no
2012-08-04 11:18 UBE - load replacements (XML)

2012-08-04
- save replacements (XML)
- use native QFileDialog

2012-08-03
- save last selected directory
- font in table cells: bigger and monospace
- performance in big files (50MB and more) is very poor! -> solved by reading complete file at once (problems at very large files > heap expected)
- copy backup, write in current file
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QRegExp>
#include <QFont>
#include <QMessageBox>
#include <QDateTime>
#include <QXmlStreamWriter>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    lastSelectedDir = QDir(QDir::rootPath()).absolutePath();

    ui->setupUi(this);
    ui->tableWidget->setFont(QFont("Courier New", 10));
    ui->statusBar->showMessage(tr("ready"));

    resizeTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonAppendLine_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
}

void MainWindow::on_pushButtonClearTable_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}

void MainWindow::setLastSelectedDir(QString fileName)
{
    // remember last folder for next time
    int lastSeperatorPos = fileName.lastIndexOf('/');
    lastSelectedDir = fileName.left(lastSeperatorPos + 1);
}

void MainWindow::on_pushButtonSelectFiles_clicked()
{
    QString caption = tr("select one or more files to open");
    QString filter = "all file-types (*.*)";
    QStringList files = QFileDialog::getOpenFileNames(this, caption, lastSelectedDir, filter);

    int lastIndex = files.length() - 1;
    for (int i = 0; i < files.length(); i++)
    {
        ui->listWidget->addItem(files.at(i));
        if (i == lastIndex)
        {
            setLastSelectedDir(files.at(lastIndex));
        }
    }
}

void MainWindow::processFileList()
{
    ui->pushButtonSearchAndReplace->setEnabled(false);

    // { copy all values, because GUI will be responsive and UI-Widgets can change
    int listWidgetCount = ui->listWidget->count();
    int tableWidgetRowCount = ui->tableWidget->rowCount();
    int tableWidgetColumnCount = ui->tableWidget->columnCount();

    QStringList listFileNames;
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        listFileNames.append(ui->listWidget->item(i)->text());
    }

    QStringList *tableContent = new QStringList[tableWidgetColumnCount];
    for (int row = 0; row < tableWidgetRowCount; row++)
    {
        for (int column = 0; column < tableWidgetColumnCount; column++)
        {
            if (ui->tableWidget->item(row, column))
            {
                tableContent[column].append(ui->tableWidget->item(row, column)->text());
            }
            else
            {
                // unvalid item -> append emtpy string for data-consistence
                tableContent[column].append("");
            }
        }
    }
    // }

    // { for all files in list, do all replecements
    for (int i = 0; i < listWidgetCount; i++)
    {
        QString outputFileName = listFileNames.at(i);
        ui->statusBar->showMessage(tr("processing file %1 of %2: %3").arg(i + 1).arg(listWidgetCount).arg(outputFileName));

        QString backupFileName = outputFileName + QDateTime::currentDateTime().toString("_yyyy-MM-dd_hh-mm-ss");
        bool fileCopied = QFile::copy(outputFileName, backupFileName);
        if (!fileCopied)
        {
            QMessageBox msgBox;
            msgBox.setText(tr("The file (%1) cannot be copied to: %2").arg(outputFileName).arg(backupFileName));
            msgBox.exec();
            continue;
        }

        QFile fileSrc(backupFileName);
        if (!fileSrc.open(QIODevice::ReadOnly))
        {
            QMessageBox msgBox;
            msgBox.setText(tr("cannot open input file (%1)").arg(backupFileName));
            msgBox.exec();
            continue;
        }


        QFile fileDst(outputFileName);
        if (!fileDst.open(QIODevice::WriteOnly))
        {
            QMessageBox msgBox;
            msgBox.setText(tr("cannot open output file (%1)").arg(outputFileName));
            msgBox.exec();
            continue;
        }

        QTextStream in(&fileSrc);
        QTextStream out(&fileDst);
        out.setCodec(in.codec()); // use same codec

        QString fileContent = in.readAll();

        // do all replacements
        for (int j = 0; j < tableWidgetRowCount; j++)
        {
            QCoreApplication::processEvents(); // keeping the GUI responsive
            if (tableContent[2].at(j) == "yes")
            {
                // search by regular expression
                QRegExp regExp(tableContent[0].at(j));
                fileContent.replace(regExp, tableContent[1].at(j));
            }
            else
            {
                // search by normal string
                QString searchString(tableContent[0].at(j));
                fileContent.replace(searchString, tableContent[1].at(j));
            }

        }
        out << fileContent;
        fileSrc.close();
        fileDst.close();
    }
    // }

    delete[] tableContent;
    ui->pushButtonSearchAndReplace->setEnabled(true);
    ui->statusBar->showMessage(tr("ready"));
}

void MainWindow::on_pushButtonSearchAndReplace_clicked()
{
    processFileList();
}

void MainWindow::clearList()
{
    ui->listWidget->clear();
}

void MainWindow::on_pushButtonClearFileList_clicked()
{
    clearList();
}

void MainWindow::resizeTable()
{
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
}

void MainWindow::on_pushButtonResizeTable_clicked()
{
    resizeTable();
}

void MainWindow::on_pushButtonSaveTable_clicked()
{
    QString fileDesciption = "RegExp XML File";
    QString caption = tr("select %1").arg(fileDesciption);
    QString filter = tr("%1 (*.xml)").arg(fileDesciption);
    QString fileName = QFileDialog::getSaveFileName(this, caption, lastSelectedDir + "RegExp.xml", filter);

    if (fileName == "")
    {
        // user aborted file selection
        return;
    }

    QFile outputFile (fileName);
    if (!outputFile.open(QIODevice::WriteOnly))
    {
        QMessageBox msgBox;
        msgBox.setText(tr("cannot open output file (%1)").arg(fileName));
        msgBox.exec();
        return;
    }

    setLastSelectedDir(fileName);

    // get table information
    int tableWidgetColumnCount = ui->tableWidget->columnCount();
    int tableWidgetRowCount = ui->tableWidget->rowCount();

    // { write XML
    QXmlStreamWriter xmlStreamWriter(&outputFile);
    xmlStreamWriter.setAutoFormatting(true);
    xmlStreamWriter.writeStartDocument();
    xmlStreamWriter.writeStartElement("RegExpTable");
    xmlStreamWriter.writeAttribute("version", "1.0");

    // write horizontal header items
    xmlStreamWriter.writeStartElement("columHeaders");
    for (int column = 0; column < tableWidgetColumnCount; column++)
    {
        xmlStreamWriter.writeTextElement("column" + QVariant(column).toString(), ui->tableWidget->horizontalHeaderItem(column)->text());
    }
    xmlStreamWriter.writeEndElement();


    // write table content
    for (int row = 0; row < tableWidgetRowCount; row++)
    {
        xmlStreamWriter.writeStartElement("row");
        for (int column = 0; column < tableWidgetColumnCount; column++)
        {
            QString content = "";
            if (ui->tableWidget->item(row, column))
            {
                content = ui->tableWidget->item(row, column)->text();
            }
            xmlStreamWriter.writeAttribute("column" + QVariant(column).toString(), content);

        }
        xmlStreamWriter.writeEndElement(); // row
    }
    xmlStreamWriter.writeEndElement(); // RegExpTable
    xmlStreamWriter.writeEndDocument();
    // } write XML

    outputFile.close();
}

void MainWindow::on_pushButtonLoadTable_clicked()
{
    QString fileDesciption = "RegExp XML File";
    QString caption = tr("select %1").arg(fileDesciption);
    QString filter = tr("%1 (*.xml)").arg(fileDesciption);
    QString fileName = QFileDialog::getOpenFileName(this, caption, lastSelectedDir, filter);

    if (fileName == "")
    {
        // user aborted file selection
        return;
    }

    QFile* file = new QFile(fileName);

    QString errorString;
    int errorLine;
    int errorColumn;

    if (!domDocument.setContent(file, true, &errorString, &errorLine, &errorColumn))
    {
        QMessageBox::information(window(), tr("RegExp"), tr("Parse error at line %1, column %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorString));
        return;
    }

    QDomNodeList rows = domDocument.documentElement().elementsByTagName("row");
    int rowCount = rows.length();
    int columnCount = ui->tableWidget->columnCount();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(rowCount);

    for (int row = 0; row < rows.count(); row++)
    {
        for (int column = 0; column < columnCount; column++)
        {
            QString content = rows.at(row).toElement().attribute("column" + QVariant(column).toString());
            QTableWidgetItem *tableWidgetItem = new QTableWidgetItem(content);
            ui->tableWidget->setItem(row, column, tableWidgetItem);
        }
    }

    file->close();
    resizeTable();
}
