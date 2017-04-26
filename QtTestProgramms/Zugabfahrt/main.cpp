#include <QtGui/QApplication>
#include "zugabfahrt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Zugabfahrt w;
    w.show();
    return a.exec();
}
