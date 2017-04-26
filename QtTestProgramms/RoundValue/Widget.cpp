#include "Widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    for (int i = -100; i < 101; i++)
    {
        double d = i / 10.0;
        int rounded;
        if (d > 0)
        {
            rounded = d + 0.5;
        }
        else
        {
            rounded = d - 0.5;
        }

        ui->plainTextEdit->appendPlainText(QString("value: %1 - rounded value: %2").arg(d).arg(rounded));
    }
}

Widget::~Widget()
{
    delete ui;
}
