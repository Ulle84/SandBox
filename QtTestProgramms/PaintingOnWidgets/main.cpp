#include <QApplication>
#include "paintingonwidgets.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintingOnWidgets w;
    w.resize(500, 500);
    w.show();
    
    return a.exec();
}
