/* ToDo
- Erweiterung auf mehrere Arbeitsbilder
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTableWidgetItem>
#include <QList>
#include <QMessageBox>

#include <QFileInfo>
#include <QtAlgorithms>
#include <QTimer>

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  evaFileLoaded = false;
  setMemberVariablesToDefault();
  ui->setupUi(this);

  // EVA File zyklisch auf Aenderungen ueberwachen
  QTimer* timer = new QTimer(this);
  timer->start(500); // alle x Millisekunden wird das Signal timeout() gesendet
  connect(timer, SIGNAL(timeout()), this, SLOT(checkTimeStampEVAFile()));

  // ToDo automatisches Ausfuehren rausschmeissen
  on_actionOpen_EVA_Results_triggered();
  //on_actionGenerate_Statistics_triggered();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::checkTimeStampEVAFile()
{
  if (!evaFileLoaded)
  {
    return;
  }

  QFileInfo fileInfo(evaFileName);

  if (evaFileLastModified == fileInfo.lastModified())
  {
    return;
  }

  QMessageBox msgBox;
  msgBox.setText("The EVA-File has been modified.");
  msgBox.setInformativeText("Do you want to reload the modified EVA-File?");
  msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
  msgBox.setDefaultButton(QMessageBox::Yes);
  int ret = msgBox.exec();

  switch (ret)
  {
  case QMessageBox::No:
    break;

  case QMessageBox::Yes:
    reloadEVAFile();
    break;

  default:
    // should never be reached
    break;
  }
}

void MainWindow::on_actionOpen_EVA_Results_triggered()
{
  // ToDo Dialog wieder aktivieren
  //evaFileName = "/Users/ulle/Dropbox/daikyo_natural_orange_Musterkatalog_TS-01-11-1180.eva";
  //QString fileName = "/Users/ulle/SVN/ullessource/EVAStatistics/examples/daikyo_natural_orange_Musterkatalog_TS-01-11-1180.eva";
  evaFileName = QFileDialog::getOpenFileName(this, tr("Open EVA File"), "", tr("EVA Result (*.eva)"));

  if (evaFileName == "")
  {
    // user aborted
    return;
  }

  processEVAFile();

}

void MainWindow::on_actionGenerate_Statistics_triggered()
{
  // get reference values
  // ToDo column number not hard-coded
  // ToDo more than one reference colum?

  QStringList referenceValues;

  QDomNodeList testCycles = domDocument.documentElement().elementsByTagName("EvaluationData").at(0).toElement().elementsByTagName("TestCycle");

  for (int i = 0; i < testCycles.length(); i++)
  {
    QDomNodeList mapEntries = testCycles.at(i).toElement().elementsByTagName("RefOutput").at(0).toElement().elementsByTagName("MapEntry");

    for (int j = 0; j < mapEntries.length(); j++)
    {
      if (mapEntries.at(j).toElement().attribute("name") == "Result")
      {
        referenceValues.append(convertHexAsciiToQString(mapEntries.at(j).toElement().text()));
      }
    }
  }


  // compare result with expected value
  int resultMatch = 0;
  int slip = 0;
  int falseReject = 0;

  for (int i = 0; i < tableRowCount; i++)
  {
    QString expected = referenceValues.at(i);

    if (!ui->tableWidget->item(i, 1))
    {
      // no valid item
      continue;
    }

    QString actual = ui->tableWidget->item(i, 1)->text();

    if (expected == actual)
    {
      resultMatch++;
    }

    if (expected == "0" && actual == "1")
    {
      slip++;
    }

    if (expected == "1" && actual == "0")
    {
      falseReject++;
    }
  }

  // ToDo output as html table ?
  ui->plainTextEdit->clear();
  ui->plainTextEdit->appendPlainText(tr("Result:"));
  ui->plainTextEdit->appendPlainText(tr("\tcorrect: %1").arg(resultMatch));
  ui->plainTextEdit->appendPlainText(tr("\tfalse reject: %1").arg(falseReject));
  ui->plainTextEdit->appendPlainText(tr("\tslip: %1").arg(slip));
  //ui->plainTextEdit->appendHtml("<div style=\"background-color: red\">test</div>");


  // prepare table if necessary
  double percentage = 5;

  if (tableRowCount == ui->tableWidget->rowCount())
  {
    QStringList additionalRowNames;
    additionalRowNames.append(tr("Minimum (all)"));
    additionalRowNames.append(tr("Maximum (all)"));
    additionalRowNames.append(tr("Minimum (good)"));
    additionalRowNames.append(tr("Maximum (good)"));
    additionalRowNames.append(tr("Minimum (good) - %1%").arg(percentage));
    additionalRowNames.append(tr("Maximum (good) + %1%").arg(percentage));
    additionalRowNames.append(tr("Minimum (bad)"));
    additionalRowNames.append(tr("Maximum (bad)"));

    ui->tableWidget->setRowCount(tableRowCount + additionalRowNames.length());

    for (int i = 0; i < additionalRowNames.length(); i++)
    {
      QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(additionalRowNames.at(i));
      ui->tableWidget->setVerticalHeaderItem(tableRowCount + i, tableWidgetItem);
      ui->tableWidget->resizeRowToContents(tableRowCount + i);
    }
  }

  for (int columnCount = 0; columnCount < ui->tableWidget->columnCount(); columnCount++)
  {
    QList<double> myListGood;
    QList<double> myListBad;
    QList<double> myListTotal;

    for (int rowCount = 0; rowCount < tableRowCount; rowCount++)
    {
      if (!ui->tableWidget->item(rowCount, columnCount))
      {
        // no valid item
        continue;
      }

      double value = ui->tableWidget->item(rowCount, columnCount)->text().toDouble();

      if (referenceValues.at(rowCount) == "1")
      {
        myListGood.append(value);
      }
      else
      {
        myListBad.append(value);
      }

      myListTotal.append(value);
    }

    qSort(myListGood.begin(), myListGood.end());
    qSort(myListBad.begin(), myListBad.end());
    qSort(myListTotal.begin(), myListTotal.end());

    // write results into table
    QStringList values;

    if (myListTotal.length() > 0)
    {
      values.append(QVariant(myListTotal.first()).toString());
      values.append(QVariant(myListTotal.last()).toString());
    }
    else
    {
      values.append("");
      values.append("");
    }

    if (myListGood.length() > 0)
    {
      double min = myListGood.first();
      double max = myListGood.last();
      double range = max - min;
      double minMinusPercentageOfRange = min - range * percentage / 100;
      double maxPlusPercentageOfRange = max + range * percentage / 100;
      values.append(QVariant(myListGood.first()).toString());
      values.append(QVariant(myListGood.last()).toString());
      values.append(QVariant(minMinusPercentageOfRange).toString());
      values.append(QVariant(maxPlusPercentageOfRange).toString());
    }
    else
    {
      values.append("");
      values.append("");
      values.append("");
      values.append("");
    }

    if (myListBad.length() > 0)
    {
      values.append(QVariant(myListBad.first()).toString());
      values.append(QVariant(myListBad.last()).toString());
    }
    else
    {
      values.append("");
      values.append("");
    }

    for (int i = 0; i < values.length(); i++)
    {
      QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(values.at(i));
      ui->tableWidget->setItem(tableRowCount + i, columnCount, tableWidgetItem);
    }
  }
}

bool MainWindow::reloadEVAFile()
{
  setMemberVariablesToDefault();
  ui->tableWidget->clear();
  ui->tableWidget->setRowCount(0);
  ui->tableWidget->setColumnCount(0);
  ui->plainTextEdit->clear();
  disconnect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_comboBox_currentIndexChanged(QString)));
  ui->comboBox->clear();
  connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_comboBox_currentIndexChanged(QString)));
  processEVAFile();
  return true;
}

bool MainWindow::setMemberVariablesToDefault()
{
  selectedVersionNumber = 0;
  tableRowCount = 0;
  outputNames.clear();
  imageNames.clear();
  versionNumbers.clear();
  return true;
}

bool MainWindow::processEVAFile()
{
  if (evaFileName == "")
  {
    return false;
  }

  QFile* file = new QFile(evaFileName);
  ui->statusBar->showMessage(evaFileName);

  QString errorStr;
  int errorLine;
  int errorColumn;

  if (!domDocument.setContent(file, true, &errorStr, &errorLine,
                              &errorColumn))
  {
    QMessageBox::information(window(), tr("XML parse error"),
                             tr("Parse error at line %1, column %2:\n%3")
                             .arg(errorLine)
                             .arg(errorColumn)
                             .arg(errorStr));
    return false;
  }

  QFileInfo fileInfo(evaFileName);
  evaFileLastModified = fileInfo.lastModified();
  file->close();

  // get workingPictureName
  QDomNodeList inputElements = domDocument.documentElement().elementsByTagName("Interface").at(0).toElement().elementsByTagName("Input").at(0).toElement().elementsByTagName("Element");

  for (int i = 0; i < inputElements.length(); i++)
  {
    QString inputElementName = inputElements.at(i).toElement().attribute("Name");

    if (inputElements.at(i).toElement().attribute("Workpic") == "true")
    {
      workingPictureName = inputElementName;
    }
  }

  // get outputNames (columns)
  QDomNodeList outputElements = domDocument.documentElement().elementsByTagName("Interface").at(0).toElement().elementsByTagName("Output").at(0).toElement().elementsByTagName("Element");

  for (int i = 0; i < outputElements.length(); i++)
  {
    QString outputElementName = outputElements.at(i).toElement().attribute("Name");
    outputNames.append(outputElementName);
  }

  // set columns in table
  ui->tableWidget->setColumnCount(outputNames.length());
  ui->tableWidget->setHorizontalHeaderLabels(outputNames);

  // get imageNames and results (rows)
  QDomNodeList testCycles = domDocument.documentElement().elementsByTagName("EvaluationData").at(0).toElement().elementsByTagName("TestCycle");

  for (int i = 0; i < testCycles.length(); i++)
  {
    QDomNodeList workpics = testCycles.at(i).toElement().elementsByTagName("Pictures").at(0).toElement().elementsByTagName("Workpic");

    for (int j = 0; j < workpics.length(); j++)
    {
      if (workpics.at(j).toElement().attribute("name") == workingPictureName)
      {
        imageNames.append(workpics.at(j).toElement().text());
      }
    }

    // set image names
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
    QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(imageNames.at(i));
    ui->tableWidget->setVerticalHeaderItem(i, tableWidgetItem);

    // get all Versionnumbers
    QDomNodeList testResults = testCycles.at(i).toElement().elementsByTagName("TestResults");

    for (int j = 0; j < testResults.length(); j++)
    {
      int versionNumber = testResults.at(j).toElement().attribute("Version").toInt();

      if (!versionNumbers.contains(versionNumber))
      {
        versionNumbers.append(versionNumber);
      }
    }
  }

  tableRowCount = ui->tableWidget->rowCount();

  disconnect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_comboBox_currentIndexChanged(QString)));

  for (int i = 0; i < versionNumbers.length(); i++)
  {
    ui->comboBox->insertItem(i, tr("Version %1").arg(versionNumbers.at(versionNumbers.length() - 1 - i)));
  }

  connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_comboBox_currentIndexChanged(QString)));

  // per default die maximale Versionsnummer verwenden
  // ToDo - dynamisch einstellbar machen
  qSort(versionNumbers.begin(), versionNumbers.end());

  if (selectedVersionNumber == 0)
  {
    selectedVersionNumber = versionNumbers.last();
  }

  evaFileLoaded = true;
  populateTable();
}

bool MainWindow::populateTable()
{
  ui->tableWidget->clearContents();
  QDomNodeList testCycles = domDocument.documentElement().elementsByTagName("EvaluationData").at(0).toElement().elementsByTagName("TestCycle");

  for (int i = 0; i < testCycles.length(); i++)
  {
    QDomNodeList testResults = testCycles.at(i).toElement().elementsByTagName("TestResults");
    QDomNodeList testResultEntries;

    for (int j = 0; j < testResults.length(); j++)
    {
      if (testResults.at(j).toElement().attribute("Version").toInt() == selectedVersionNumber)
      {
        testResultEntries = testResults.at(j).toElement().elementsByTagName("MapEntry");
      }
    }

    for (int j = 0; j < testResultEntries.length(); j++)
    {
      QString testResultName = testResultEntries.at(j).toElement().attribute("name");
      int index = outputNames.indexOf(testResultName);
      QString value = convertHexAsciiToQString(testResultEntries.at(j).toElement().text());
      QTableWidgetItem* tableWidgetItem = new QTableWidgetItem(value);
      ui->tableWidget->setItem(i, index, tableWidgetItem);
    }
  }

  ui->tableWidget->resizeColumnsToContents();
  ui->tableWidget->resizeRowsToContents();

  on_actionGenerate_Statistics_triggered();
  return true;
}

QString MainWindow::convertHexAsciiToQString(QString HexAscii)
{
  QStringList singleCharacters = HexAscii.split(" ");
  QString result = "";

  for (int i = 0; i < singleCharacters.length(); i++)
  {
    // ToDo performanter programmieren
    // ToDo komplette Ascii-Tabelle ?
    if (singleCharacters.at(i) == "20")
    {
      result.append(' ');
    }

    if (singleCharacters.at(i) == "2B")
    {
      result.append('+');
    }

    if (singleCharacters.at(i) == "2C")
    {
      result.append(',');
    }

    if (singleCharacters.at(i) == "2D")
    {
      result.append('-');
    }

    if (singleCharacters.at(i) == "2E")
    {
      result.append('.');
    }

    if (singleCharacters.at(i) == "30")
    {
      result.append('0');
    }

    if (singleCharacters.at(i) == "31")
    {
      result.append('1');
    }

    if (singleCharacters.at(i) == "32")
    {
      result.append('2');
    }

    if (singleCharacters.at(i) == "33")
    {
      result.append('3');
    }

    if (singleCharacters.at(i) == "34")
    {
      result.append('4');
    }

    if (singleCharacters.at(i) == "35")
    {
      result.append('5');
    }

    if (singleCharacters.at(i) == "36")
    {
      result.append('6');
    }

    if (singleCharacters.at(i) == "37")
    {
      result.append('7');
    }

    if (singleCharacters.at(i) == "38")
    {
      result.append('8');
    }

    if (singleCharacters.at(i) == "39")
    {
      result.append('9');
    }
  }

  return result;
}

void MainWindow::processCSVFile(QString filename)
{
  QFile file(filename);
  ui->statusBar->showMessage(filename);

  if (file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QStringList rows;

    while (!file.atEnd())
    {
      rows.append(file.readLine());
    }

    for (int rowCount = 0; rowCount < rows.length(); rowCount++)
    {
      QStringList columns = rows.at(rowCount).split("\t");

      // set up table
      if (rowCount == 0)
      {
        ui->tableWidget->setRowCount(rows.length() - 1);
        ui->tableWidget->setColumnCount(columns.length() - 1);
        ui->tableWidget->setHorizontalHeaderLabels(columns.mid(1, rows.length() - 1));
        continue;
      }

      // fill table with elements
      for (int columnCount = 0; columnCount < columns.length(); columnCount++)
      {
        QTableWidgetItem* temp = new QTableWidgetItem(columns.at(columnCount));

        if (columnCount == 0)
        {
          ui->tableWidget->setVerticalHeaderItem(rowCount - 1, temp);
        }
        else
        {
          ui->tableWidget->setItem(rowCount - 1, columnCount - 1, temp);
        }
      }
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

    file.close();
  }
}


void MainWindow::on_comboBox_currentIndexChanged(const QString& arg1)
{
  QStringList splitted = arg1.split(" ");
  selectedVersionNumber = splitted.at(1).toInt();
  populateTable();
}

void MainWindow::on_actionReload_EVA_File_triggered()
{
  reloadEVAFile();
}
