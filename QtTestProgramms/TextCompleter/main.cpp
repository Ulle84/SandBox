#include <QApplication>
#include "TextCompleter.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  TextCompleter w;
  w.show();
  
  return a.exec();
}
