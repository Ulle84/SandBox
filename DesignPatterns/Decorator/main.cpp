#include "DecoratorExample.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  DecoratorExample w;
  w.show();

  return a.exec();
}
