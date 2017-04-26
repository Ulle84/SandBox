#ifndef TOUCHEDITFIELD_H
#define TOUCHEDITFIELD_H

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QLineEdit>

class TouchEditField : public QWidget
{
    Q_OBJECT

private:
    QLineEdit* lineEdit;
    QPushButton* pushButton0;
    QPushButton* pushButton1;
    QPushButton* pushButton2;
    QPushButton* pushButton3;
    QPushButton* pushButton4;
    QPushButton* pushButton5;
    QPushButton* pushButton6;
    QPushButton* pushButton7;
    QPushButton* pushButton8;
    QPushButton* pushButton9;
    QPushButton* pushButtonComma;

private slots:
    void insert0();
    void insert1();
    void insert2();
    void insert3();
    void insert4();
    void insert5();
    void insert6();
    void insert7();
    void insert8();
    void insert9();
    void insertComma();
    void interpretLineEdit();

public:
    TouchEditField(QWidget *parent = 0);
    ~TouchEditField();
};

#endif // TOUCHEDITFIELD_H
