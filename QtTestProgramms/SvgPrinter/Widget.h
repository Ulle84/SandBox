#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
  Q_OBJECT

public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

private slots:
  void on_webView_loadFinished(bool loadFinished);

private:
  Ui::Widget *ui;
  void print();
};

#endif // WIDGET_H
