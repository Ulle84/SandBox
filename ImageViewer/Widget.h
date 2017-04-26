#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWheelEvent>

class QTimer;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool eventFilter(QObject *target, QEvent *event);

private slots:
    void showImage();
    
    void on_spinBox_valueChanged(int interval);

    void on_checkBoxRandom_stateChanged(int state);

private:
    void parseBaseFolder();

    Ui::Widget *ui;
    QStringList imagePaths;
    QTimer* timer;
    int currentIndex;
};

#endif // WIDGET_H
