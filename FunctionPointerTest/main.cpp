#include <QCoreApplication>
#include <QDebug>

// for using function pointers the function has to be global or a static method of a class

bool printDoubles (double value1, double value2)
{
    qDebug() << value1 << value2;
}

class MyClass {
public:
    static void printDoublesDirectly(double value1, double value2);
    void printDoublesIndirectly(double value1, double value2);
};

void MyClass::printDoublesDirectly(double value1, double value2)
{
    qDebug() << value1 << value2;
}

void MyClass::printDoublesIndirectly(double value1, double value2)
{
    void (*funcptr)(double, double) = printDoublesDirectly;m

    (*funcptr)(value1, value2);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "start of application";

    qDebug() << "call printDoubles directly";
    printDoubles(1.2, 2.3);

    bool (*funcptr)(double, double) = printDoubles;

    qDebug() << "call printDoubles via function pointer";
    (*funcptr)(3.4, 4.5);

    MyClass myClass;
    qDebug() << "call myClass::printDoublesDirectly";
    myClass.printDoublesDirectly(5.6, 6.7);
    myClass.printDoublesIndirectly(7.8, 8.9);

    return a.exec();
}

