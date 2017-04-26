#include "toucheditfield.h"

#include <QtGui/QGridLayout>
#include <QString>
#include <QVariant>
#include <QDoubleValidator>
#include <QFont>

#include <iostream>

/* ToDo
  - Backwards-Button
  - OK-Button
*/

TouchEditField::TouchEditField(QWidget *parent)
    : QWidget(parent)
{
    // init widgets
    lineEdit = new QLineEdit();
    pushButton0 = new QPushButton("0");
    pushButton1 = new QPushButton("1");
    pushButton2 = new QPushButton("2");
    pushButton3 = new QPushButton("3");
    pushButton4 = new QPushButton("4");
    pushButton5 = new QPushButton("5");
    pushButton6 = new QPushButton("6");
    pushButton7 = new QPushButton("7");
    pushButton8 = new QPushButton("8");
    pushButton9 = new QPushButton("9");
    pushButtonComma = new QPushButton(",");

    // font for buttons
    QFont* font = new QFont("Verdana", 24, QFont::Bold, false);

    // change settings of widgets
    lineEdit->setValidator(new QDoubleValidator());
    //lineEdit->setFont(*font);
    //lineEdit->
    pushButton0->setFont(*font);
    pushButton1->setFont(*font);
    pushButton2->setFont(*font);
    pushButton3->setFont(*font);
    pushButton4->setFont(*font);
    pushButton5->setFont(*font);
    pushButton6->setFont(*font);
    pushButton7->setFont(*font);
    pushButton8->setFont(*font);
    pushButton9->setFont(*font);
    pushButtonComma->setFont(*font);

    // create layout
    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(lineEdit, 0, 0, 1, 3);
    gridLayout->addWidget(pushButton0, 4, 0, 1, 2);
    gridLayout->addWidget(pushButton1, 3, 0);
    gridLayout->addWidget(pushButton2, 3, 1);
    gridLayout->addWidget(pushButton3, 3, 2);
    gridLayout->addWidget(pushButton4, 2, 0);
    gridLayout->addWidget(pushButton5, 2, 1);
    gridLayout->addWidget(pushButton6, 2, 2);
    gridLayout->addWidget(pushButton7, 1, 0);
    gridLayout->addWidget(pushButton8, 1, 1);
    gridLayout->addWidget(pushButton9, 1, 2);
    gridLayout->addWidget(pushButtonComma, 4, 2);

    // connect signals and slots
    connect(pushButton0, SIGNAL(clicked()), this, SLOT(insert0()));
    connect(pushButton1, SIGNAL(clicked()), this, SLOT(insert1()));
    connect(pushButton2, SIGNAL(clicked()), this, SLOT(insert2()));
    connect(pushButton3, SIGNAL(clicked()), this, SLOT(insert3()));
    connect(pushButton4, SIGNAL(clicked()), this, SLOT(insert4()));
    connect(pushButton5, SIGNAL(clicked()), this, SLOT(insert5()));
    connect(pushButton6, SIGNAL(clicked()), this, SLOT(insert6()));
    connect(pushButton7, SIGNAL(clicked()), this, SLOT(insert7()));
    connect(pushButton8, SIGNAL(clicked()), this, SLOT(insert8()));
    connect(pushButton9, SIGNAL(clicked()), this, SLOT(insert9()));
    connect(pushButtonComma, SIGNAL(clicked()), this, SLOT(insertComma()));
    connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(interpretLineEdit()));

    setLayout(gridLayout);
}

TouchEditField::~TouchEditField()
{

}

void TouchEditField::insert0() {
    lineEdit->insert("0");
}

void TouchEditField::insert1() {
    lineEdit->insert("1");
}

void TouchEditField::insert2() {
    lineEdit->insert("2");
}

void TouchEditField::insert3() {
    lineEdit->insert("3");
}

void TouchEditField::insert4() {
    lineEdit->insert("4");
}

void TouchEditField::insert5() {
    lineEdit->insert("5");
}

void TouchEditField::insert6() {
    lineEdit->insert("6");
}

void TouchEditField::insert7() {
    lineEdit->insert("7");
}

void TouchEditField::insert8() {
    lineEdit->insert("8");
}

void TouchEditField::insert9() {
    lineEdit->insert("9");
}

void TouchEditField::insertComma() {
    lineEdit->insert(",");
}

void TouchEditField::interpretLineEdit() {
    std::cout << QVariant(lineEdit->text()).toDouble() << std::endl;
}
