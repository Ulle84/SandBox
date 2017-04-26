#include <algorithm>
#include <iostream>
#include <vector>

#include <QCoreApplication>
#include <QDebug>

int op_increase (int i)
{
  return ++i;
}

int op_add(int i, int j)
{
  return i + j;
}


int op_multiply(int i, int j)
{
  return i * j;
}

void initMatrix(std::vector<std::vector<int>>& matrix, int width, int height)
{
  matrix.resize(height);

  for (int i = 0; i < height; ++i)
  {
    matrix[i].resize(width);
  }

  // fill with values
  for (int i = 0; i < height; ++i)
  {
    for (int j = 0; j < width; ++j)
    {
      matrix[i][j] = width * i + j;
    }
  }
}

void printMatrix(std::vector<std::vector<int>> matrix, int width, int height)
{
  for (int i = 0; i < height; ++i)
  {
    for (int j = 0; j < width; ++j)
    {
      if (matrix[i][j] < 10)
      {
        std::cout << " ";
      }

      if (matrix[i][j] < 100)
      {
        std::cout << " ";
      }

      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  std::vector<int> vec1;
  std::vector<int> vec2;
  std::vector<int> vec3;

  int size = 3;
  vec1.resize(size);
  vec2.resize(size);
  vec3.resize(size);

  // set some values
  for (int i = 0; i < size; i++)
  {
    vec1[i] = (i * 10);
    vec2[i] = (i * 20);
  }

  qDebug() << "vec1";
  for (int i = 0; i < size; i++)
  {
    qDebug() << vec1[i];
  }
  qDebug() << '\n';

  qDebug() << "vec2";
  for (int i = 0; i < size; i++)
  {
    qDebug() << vec2[i];
  }
  qDebug() << '\n';

  // unary transformation
  std::transform (vec1.begin(), vec1.end(), vec3.begin(), op_increase);

  qDebug() << "vec1++";
  for (int i = 0; i < size; i++)
  {
    qDebug() << vec3[i];
  }
  qDebug() << '\n';

  // binary transformation
  std::transform (vec1.begin(), vec1.end(), vec2.begin(), vec3.begin(), op_multiply);

  qDebug() << "vec1 * vec2";
  for (int i = 0; i < size; i++)
  {
    qDebug() << vec3[i];
  }
  qDebug() << '\n';


  int width = 5;
  int height = 3;
  std::vector<std::vector<int>> matrix;
  initMatrix(matrix, width, height);
  printMatrix(matrix, width, height);

  qDebug() << "finished";

  return a.exec();
}
