#include <QApplication>
#include "AnalyseDoneList.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  AnalyseDoneList w;
  w.show();

  return a.exec();
}
