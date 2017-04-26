#include <QApplication>
#include "ViDiagToLog4Cxx.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ViDiagToLog4Cxx w;
  w.show();
  
  return a.exec();
}
