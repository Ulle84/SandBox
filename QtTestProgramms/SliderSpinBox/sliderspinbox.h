#ifndef SLIDERSPINBOX_H
#define SLIDERSPINBOX_H

#include <QWidget>

namespace Ui {
class SliderSpinBox;
}

class SliderSpinBox : public QWidget
{
    Q_OBJECT
    
public:
    explicit SliderSpinBox(QWidget *parent = 0);
    ~SliderSpinBox();

public slots:
    void setMaximum(int maximum);
    void setMinimum(int minimum);

signals:
    void valueChanged(int newValue);
    
private:
    Ui::SliderSpinBox *ui;
    int minimum;
    int maximum;
};

#endif // SLIDERSPINBOX_H
