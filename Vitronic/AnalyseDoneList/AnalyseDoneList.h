#ifndef ANALYSEDONELIST_H
#define ANALYSEDONELIST_H

#include <QWidget>
#include <QDate>

namespace Ui
{
class AnalyseDoneList;
}

class AnalyseDoneList : public QWidget
{
  Q_OBJECT

public:
  explicit AnalyseDoneList(QWidget* parent = 0);
  ~AnalyseDoneList();

private slots:
  void on_calendarWidgetStartDate_clicked(const QDate& date);

  void on_calendarWidgetEndDate_clicked(const QDate& date);

private:
  Ui::AnalyseDoneList* ui;
  void AnalyseMLFile();
  QDate startDate;
  QDate endDate;
};

#endif // ANALYSEDONELIST_H
