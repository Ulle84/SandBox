#include <QApplication>
#include "sliderspinbox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SliderSpinBox w;
    w.show();
    
    return a.exec();
}
