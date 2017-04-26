/* ToDo
- do not use the dom-parser - it needs a lot of memory!
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

// xml
#include <QDomDocument>

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_pushButtonClearList_clicked()
{
  ui->listWidget->clear();
}

void MainWindow::on_pushButtonSelectFiles_clicked()
{
  QString caption = tr("select one or more EVA file to open");
  QString filter = "EVA files (*.eva)";
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

void MainWindow::on_pushButtonDeleteEvaluationData_clicked()
{
  for (int i = 0; i < ui->listWidget->count(); i++)
  {
    QString fileName = ui->listWidget->item(i)->text();
    QFile* file = new QFile(fileName);

    if (!file->open(QIODevice::ReadOnly))
    {
      QMessageBox messageBox;
      messageBox.setText(tr("could not open file: %1 for reading").arg(fileName));
      messageBox.exec();
      continue;
    }

    ui->statusBar->showMessage(fileName);

    QString errorStr;
    int errorLine;
    int errorColumn;

    QDomDocument domDocument;

    if (!domDocument.setContent(file, true, &errorStr, &errorLine, &errorColumn))
    {
      QString errorString = tr("Parse error at line %1, column %2:\n%3").arg(errorLine).arg(errorColumn).arg(errorStr);
      QMessageBox::information(window(), tr("XML parse error"), errorString);
      return;
    }

    file->close();

    // remove EvalutationData
    QDomNodeList domNodeList = domDocument.elementsByTagName("EvaluationData");

    for (int j = 0; j < domNodeList.length(); j++)
    {
      QApplication::processEvents(); // keeping the GUI responsive
      QDomNode domNode = domNodeList.at(j);
      domNode.parentNode().removeChild(domNode);
    }

    if (!file->open(QIODevice::WriteOnly))
    {
      QMessageBox messageBox;
      messageBox.setText(tr("could not open file: %1 for writing").arg(fileName));
      messageBox.exec();
      continue;
    }

    QTextStream out(file);
    domDocument.save(out, 2);

    file->close();
  }

  ui->statusBar->showMessage(tr("ready"));
}

void MainWindow::setLastSelectedDir(QString fileName)
{
  // remember last folder for next time
  int lastSeperatorPos = fileName.lastIndexOf('/');
  lastSelectedDir = fileName.left(lastSeperatorPos + 1);
}
