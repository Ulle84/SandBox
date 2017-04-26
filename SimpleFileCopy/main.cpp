#include <QApplication>
#include "SimpleFileCopy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimpleFileCopy w;
    w.show();
    
    return a.exec();
}
