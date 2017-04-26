#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui
{
class Widget;
}

class Widget : public QWidget
{
  Q_OBJECT

public:
  explicit Widget(QWidget* parent = 0);
  ~Widget();

private slots:
  void on_comboBox_currentIndexChanged(const QString& string);

private:
  Ui::Widget* ui;
  int constFormLayoutLines;
};

#endif // WIDGET_H
