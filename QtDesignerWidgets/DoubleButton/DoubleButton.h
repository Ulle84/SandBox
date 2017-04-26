#ifndef DOUBLEBUTTON_H
#define DOUBLEBUTTON_H

#include <QWidget>
#include <QStringList>
#include <QVariantMap>

namespace Ui
{
class DoubleButton;
}

class DoubleButton : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QString buttonText1 READ buttonText1 WRITE setButtonText1)
  Q_PROPERTY(QString buttonText2 READ buttonText2 WRITE setButtonText2)


public:
  explicit DoubleButton(QWidget* parent = 0);
  ~DoubleButton();

  QString buttonText1();
  QString buttonText2();

  void setButtonText1(const QString& buttonText1);
  void setButtonText2(const QString& buttonText2);

private slots:
  void on_pushButton1_clicked();
  void on_pushButton2_clicked();

private:
  Ui::DoubleButton* ui;
  QStringList m_test;
  QVariantMap m_variantMap;
};

#endif // DOUBLEBUTTON_H
