#include <QtGui/QApplication>
#include "toucheditfield.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TouchEditField w;
    w.resize(400, 200);
    w.show();

    return a.exec();
}
