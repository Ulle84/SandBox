#ifndef LADDERSCALCULATOR_H
#define LADDERSCALCULATOR_H

#include <QWidget>

namespace Ui {
class LaddersCalculator;
}

class LaddersCalculator : public QWidget
{
  Q_OBJECT

public:
  explicit LaddersCalculator(QWidget *parent = 0);
  ~LaddersCalculator();

private slots:
  void on_lineEditInput_textEdited(const QString& input);

private:
  Ui::LaddersCalculator *ui;
};

#endif // LADDERSCALCULATOR_H
