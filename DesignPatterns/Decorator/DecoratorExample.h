#ifndef DECORATOREXAMPLE_H
#define DECORATOREXAMPLE_H

#include <QWidget>

class Component;
class Decorator;

namespace Ui {
class DecoratorExample;
}

class DecoratorExample : public QWidget
{
  Q_OBJECT

public:
  explicit DecoratorExample(QWidget *parent = 0);
  ~DecoratorExample();

private slots:
  void on_pushButtonOperateComponent_clicked();
  void on_pushButtonOperateDecorator_clicked();
  void on_pushButtonOperateDoubleDecorator_clicked();

private:
  Ui::DecoratorExample *ui;
  Component* mComponent;
  Decorator* mDecorator;
  Decorator* mDoubleDecorator;
};

#endif // DECORATOREXAMPLE_H
