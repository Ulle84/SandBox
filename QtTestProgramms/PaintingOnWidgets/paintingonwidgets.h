#ifndef PAINTINGONWIDGETS_H
#define PAINTINGONWIDGETS_H

#include <QWidget>

class PaintingOnWidgets : public QWidget
{
    Q_OBJECT
    
public:
    PaintingOnWidgets(QWidget *parent = 0);
    ~PaintingOnWidgets();

private:
    void paintEvent(QPaintEvent *);
};

#endif // PAINTINGONWIDGETS_H
