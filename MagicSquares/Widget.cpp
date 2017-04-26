#include "Widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
}

Widget::~Widget()
{
  delete ui;
}

void Widget::generateMagicSquares()
{
  for (int length = 5; length < ui->spinBoxMax->value(); length += 2)
  {
    QApplication::processEvents();
    int* square = new int [length * length];
    /*int** square = new int* [length];
    for (int i = 0; i < length; i++)
    {
      square[i] = new int[length];
    }*/
    memset(square, 0, sizeof(int) * length * length);

    // top left corner is the origin
    int x = length / 2;
    int y = 0;
    for (int i = 1; i <= length * length; i++)
    {
      if(square[y * length + x] == 0)
      {
        // place is empty
        square[y * length + x] = i;
      }
      else
      {
        y += 2;
        if (y >= length)
        {
          y -= length;
        }
        if (y < 0)
        {
          y = length + y;
        }
        x -= 1;
        if (x >= length)
        {
          x -= length;
        }
        if (x < 0)
        {
          x = length + x;
        }
        square[y * length + x] = i;
      }
      y -= 1;
      if (y >= length)
      {
        y -= length;
      }
      if (y < 0)
      {
        y = length + y;
      }
      x += 1;
      if (x >= length)
      {
        x -= length;
      }
      if (x < 0)
      {
        x = length + x;
      }
    }

    // check solution
    int checkSum = 0;
    for (int i = 0; i < length; i++)
    {
      checkSum += square[i];
    }

    // check all lines except first one
    for (int i = 1; i < length; i++)
    {
      int sum = 0;
      for (int j = 0; j < length; j++)
      {
        sum += square[i * length + j];
      }
      if (sum != checkSum)
      {
        ui->plainTextEdit->appendPlainText("invalid checksum!");
        return;
      }
    }

    // check all columns
    for (int i = 0; i < length; i++)
    {
      int sum = 0;
      for (int j = 0; j < length; j++)
      {
        sum += square[j * length + i];
      }
      if (sum != checkSum)
      {
        ui->plainTextEdit->appendPlainText("invalid checksum!");
        return;
      }
    }

    ui->plainTextEdit->appendPlainText(tr("solution for magic square #%1 is correct!").arg(length));



    // print solution
    /*ui->plainTextEdit->appendPlainText(tr("this is magic square #%1").arg(length));
    for (int i = 0; i < length; i++)
    {
      QString text;
      for (int j = 0; j < length; j++)
      {
        text.append(QString(" %1").arg(square[i * length + j]));
      }
      ui->plainTextEdit->appendPlainText(text);
    }*/

    delete[] square;
  }
}

void Widget::on_pushButton_clicked()
{
    generateMagicSquares();
}
