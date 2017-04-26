#include <QtGui/QApplication>
#include <QtGui>
#include "diary.h"
#include <iostream>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  Diary w;
  w.resize(1000, 600);
  w.show();

  // Standardgröße von QCalendarWidget herausfinden
  // QCalendarWidget *calendarWidget = new QCalendarWidget;
  // calendarWidget->show();
  // std::cout << calendarWidget->height() << " " << calendarWidget->width();
  return a.exec();
}
