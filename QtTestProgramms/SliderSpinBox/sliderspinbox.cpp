#include "sliderspinbox.h"
#include "ui_sliderspinbox.h"

SliderSpinBox::SliderSpinBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliderSpinBox)
{
    minimum = 0;
    maximum = 100;

    ui->setupUi(this);

    ui->horizontalSlider->setMinimum(minimum);
    ui->horizontalSlider->setMaximum(maximum);

    ui->spinBox->setMinimum(minimum);
    ui->spinBox->setMaximum(maximum);

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->spinBox, SLOT(setValue(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
}

SliderSpinBox::~SliderSpinBox()
{
    delete ui;
}

void SliderSpinBox::setMaximum(int maximum)
{
    ui->horizontalSlider->setMaximum(maximum);
    ui->spinBox->setMaximum(maximum);
}

void SliderSpinBox::setMinimum(int minimum)
{
    ui->horizontalSlider->setMinimum(minimum);
    ui->spinBox->setMinimum(minimum);
}
