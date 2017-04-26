#include "AnalyseDoneList.h"
#include "ui_AnalyseDoneList.h"

#include <QXmlStreamReader>
#include <QDomDocument>
#include <QFile>
#include <QMessageBox>
#include <QDate>
#include <QStringList>

AnalyseDoneList::AnalyseDoneList(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::AnalyseDoneList)
{
  ui->setupUi(this);
  startDate = QDate::currentDate().addDays(-7);
  ui->calendarWidgetStartDate->setSelectedDate(startDate);
  endDate = QDate::currentDate();
  AnalyseMLFile();
}

AnalyseDoneList::~AnalyseDoneList()
{
  delete ui;
}

void AnalyseDoneList::AnalyseMLFile()
{
  ui->plainTextEditResult->clear();
  QString fileName = "E:\\Verschiedenes\\ToDoListen\\todo.done.tdl";

  QFile* file = new QFile(fileName);

  QString errorStr;
  int errorLine;
  int errorColumn;

  QDomDocument domDocument;

  if (!domDocument.setContent(file, true, &errorStr, &errorLine,
                              &errorColumn))
  {
    QMessageBox::information(window(), tr("XML parse error"),
                             tr("Parse error at line %1, column %2:\n%3")
                             .arg(errorLine)
                             .arg(errorColumn)
                             .arg(errorStr));
    return;
  }

  QDomNodeList tasks = domDocument.documentElement().elementsByTagName("TASK");

  QStringList doneList;

  for (int i = 0; i < tasks.length(); i++)
  {
    QString doneDateString = tasks.at(i).toElement().attribute("DONEDATESTRING");
    doneDateString = doneDateString.left(10);

    QDate doneDate = QDate::fromString(doneDateString, "yyyy-MM-dd");

    if (startDate <= doneDate && doneDate <= endDate)
    {
      QString title = tasks.at(i).toElement().attribute("TITLE");

      if (title.length() > 0)
      {
        doneList.append(QString("%1 - %2").arg(doneDate.toString("yyyy-MM-dd (ddd)")).arg(title));
      }
    }
  }

  doneList.sort();

  for (int i = 0; i < doneList.length(); i++)
  {
    ui->plainTextEditResult->appendPlainText(doneList.at(i));
  }
}

void AnalyseDoneList::on_calendarWidgetStartDate_clicked(const QDate& date)
{
  startDate = date;
  AnalyseMLFile();
}

void AnalyseDoneList::on_calendarWidgetEndDate_clicked(const QDate& date)
{
  endDate = date;
  AnalyseMLFile();
}
