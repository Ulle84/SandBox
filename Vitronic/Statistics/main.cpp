#include <QtCore/QCoreApplication>
#include <iostream>

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QList>
#include <QVariant>
#include <math.h>
#include <QtAlgorithms>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bool skipFirstLine = false;
    int column = 0;
    bool printValues = false;

    if (argc < 2) {
        cout << "usage: "                                 << endl;
        cout << "1. Parameter - File"                     << endl;
        cout << "2. Parameter - Column (starting with 0)" << endl;
        cout << "3. Parameter - SkipFirstLine (1 or 0)"   << endl;
        cout << "4. Parameter - PrintValues (1 or 0)"     << endl;
        return -1;
    }

    QString fileString;
    if (argc > 1) {
        fileString = QVariant(argv[1]).toString();
    }

    if (argc > 2) {
        column = QVariant(argv[2]).toInt();
    }
    if (argc > 3) {
        skipFirstLine = QVariant(argv[3]).toBool();
    }
    if (argc > 4) {
        printValues = QVariant(argv[4]).toBool();
    }

    QFile *srcFile = new QFile(fileString);
    if (!srcFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        return -1;
    }

    QTextStream in(srcFile);
    QString line;
    QStringList stringList;
    QList<double> list;

    if (skipFirstLine) {
       line = in.readLine();
    }

    while (!in.atEnd()) {
        line = in.readLine();
        stringList = line.split("\t");
        if (stringList.length() > column) {
            list.push_back(QVariant(stringList.at(column)).toDouble());
        }
    }

    if (list.length() < 2) {
        return -1;
    }

    double maximum = 0;
    double minimum = 9999999999999;
    double mittelwert = 0;
    double spannweite = 0;
    double standardabweichung = 0;
    double value;
    double sum = 0;

    for (int i = 0; i < list.length(); i++) {
        value = list.at(i);
        if (printValues) {
            cout << value << endl;
        }
        if (value > maximum) {
            maximum = value;
        }
        if (value < minimum) {
            minimum = value;
        }
        sum += value;
    }

    mittelwert = sum / list.length();

    double tempSum = 0;
    for (int i = 0; i < list.length(); i++) {
        value = list.at(i);
        tempSum += (value - mittelwert) * (value - mittelwert);
    }
    standardabweichung = sqrt(1.0 / (list.length() - 1.0) * tempSum);

    spannweite = maximum - minimum;

    qSort(list);

    double median = 0;
    int halfLength = list.length()/2;
    if (list.length() % 2 == 1) {
        median = list.at(halfLength);
    }
    else {
        median = (list.at(halfLength) + list.at(halfLength - 1)) / 2.0;
    }

    cout << "Anzahl der Messwerte: " << list.count() << endl;
    cout << "Mittelwert: " << mittelwert << endl;
    cout << "Standardabweichung: " << standardabweichung << endl;
    cout << "Maximum: " << maximum << endl;
    cout << "Minimum: " << minimum << endl;
    cout << "Spannweite: " << spannweite << endl;
    cout << "Median: " << median << endl;

    return a.exec();
}
