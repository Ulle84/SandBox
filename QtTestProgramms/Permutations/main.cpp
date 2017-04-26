#include <QApplication>
#include "Permutations.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Permutations w;
    w.show();
    
    return a.exec();
}
