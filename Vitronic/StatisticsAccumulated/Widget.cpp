#include "Widget.h"
#include "ui_Widget.h"

#include <stdlib.h>

#include <QList>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    doCalculation();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::doCalculation()
{
    // fill list
    QList<double> values;
    for (int i = 0; i < 100; i++)
    {
        int randomValue = rand() % 65536;
        values.append(randomValue);
    }

    // calculate statistics
    ui->plainTextEdit->appendPlainText("calculate statistics");
    double meanValue = 0.0;
    double stdDeviation = 0.0;
    for (int i = 0; i < values.length(); i++)
    {
        meanValue += values.at(i);
    }
    meanValue /= values.length();

    for (int i = 0; i < values.length(); i++)
    {
        double diff = values.at(i) - meanValue;
        double diff2 = diff * diff;
        stdDeviation += diff2;
    }
    stdDeviation /= values.length() - 1;
    stdDeviation = sqrt(stdDeviation);
    ui->plainTextEdit->appendPlainText(QString("mean value: %1").arg(meanValue));
    ui->plainTextEdit->appendPlainText(QString("std deviation: %1").arg(stdDeviation));

    // calculate statisticis by accumulation
    ui->plainTextEdit->appendPlainText("\ncalculate statistics by accumulation");
    meanValue = 0.0;
    stdDeviation = 0.0;

    double sumOfValues = 0.0;
    double sumOfSquaredValues = 0.0;
    for (int i = 0; i < values.length(); i++)
    {
        sumOfValues += values.at(i);
        sumOfSquaredValues += values.at(i) * values.at(i);
    }
    meanValue = sumOfValues / values.length();
    stdDeviation = sqrt((sumOfSquaredValues - sumOfValues * sumOfValues / values.length()) / (values.length() - 1));
    ui->plainTextEdit->appendPlainText(QString("mean value: %1").arg(meanValue));
    ui->plainTextEdit->appendPlainText(QString("std deviation: %1").arg(stdDeviation));
}
