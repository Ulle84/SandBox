#include "LaddersCalculator.h"
#include "ui_LaddersCalculator.h"

#include <vector>

#include <QStringList>

LaddersCalculator::LaddersCalculator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::LaddersCalculator)
{
  ui->setupUi(this);
}

LaddersCalculator::~LaddersCalculator()
{
  delete ui;
}

void LaddersCalculator::on_lineEditInput_textEdited(const QString& input)
{
  ui->lineEditOutput->clear();

  // calculate ladders -> formula: (max - min + 1) x (max + min) / 2
  // 1 3 -> 1 + 2 + 3 -> 6
  // 4 6 -> 4 + 5 + 6 -> 15
  // 3 7 -> 3 + 4 + 5 + 6 + 7 -> 25
  // 7 3 -> 7 + 6 + 5 + 4 + 3 -> 25
  // 1 4 1 -> 1 + 2 + 3 + 4 + 3 + 2 + 1 -> 16
  // 1 12 8 -> 116

  // extract numbers
  QStringList numbers = input.split(" ");

  if (numbers.length() == 0)
  {
    return;
  }

  std::vector<int> numbersVector;
  for (auto it = numbers.begin(); it != numbers.end(); ++it)
  {
    bool conversionOkay = false;
    int number = it->toInt(&conversionOkay);

    if (conversionOkay)
    {
      numbersVector.push_back(number);
    }
  }

  if (numbersVector.size() < 2)
  {
    return;
  }

  // calculate ladder
  int value = 0;

  for (int i  = 0; i < (numbersVector.size() - 1); i++)
  {
    int min = numbersVector[i];
    int max = numbersVector[i+1];

    if (max < min)
    {
      int swap = min;
      min = max;
      max = swap;
    }
    value += (max - min + 1) * (max + min) / 2;

    if (i != numbersVector.size() - 2)
    {
      value -= max;
    }
  }

  ui->lineEditOutput->setText(QString("%1").arg(value));
}
