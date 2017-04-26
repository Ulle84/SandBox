#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>

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
  void on_pushButtonCreateClass_clicked();

private:
  Ui::Widget* ui;
  QString createContentHeader();
  QString createContentImplementation();
  void writeFile(QString fileExtension, QString fileContent);
  QString getFilePathWithoutExtension();
};

#endif // WIDGET_H
