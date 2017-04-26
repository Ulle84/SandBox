#ifndef DOUBLEBUTTONDIALOG_H
#define DOUBLEBUTTONDIALOG_H

#include <QDialog>

class DoubleButton;

namespace Ui
{
class DoubleButtonDialog;
}

class DoubleButtonDialog : public QDialog
{
  Q_OBJECT

public:
  explicit DoubleButtonDialog(DoubleButton* doubleButton = 0, QWidget* parent = 0);
  ~DoubleButtonDialog();

  QString buttonText1();
  QString buttonText2();

  void setButtonText1(const QString& buttonText1);
  void setButtonText2(const QString& buttonText2);

private slots:
  void on_buttonBox_accepted();

private:
  Ui::DoubleButtonDialog* ui;
  DoubleButton* m_doubleButton;
};

#endif // DOUBLEBUTTONDIALOG_H
