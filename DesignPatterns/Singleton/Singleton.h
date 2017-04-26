#ifndef SINGLETON_H
#define SINGLETON_H

#include <QWidget>

namespace Ui {
class Singleton;
}

class Singleton : public QWidget
{
  Q_OBJECT

public:
  explicit Singleton(QWidget *parent = 0);
  ~Singleton();

private slots:
  void on_pushButtonAccessSingleton_clicked();

private:
  Ui::Singleton *ui;
};

#endif // SINGLETON_H
