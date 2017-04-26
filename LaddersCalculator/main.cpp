#include <QApplication>
#include "LaddersCalculator.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  LaddersCalculator w;
  w.show();
  
  return a.exec();
}
