#include "PlayingField.h"

#include <iostream>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QVariant>

PlayingField::PlayingField()
{
  flings = new QList<Fling>();
}

PlayingField::PlayingField(QString fileName)
{
  flings = new QList<Fling>();

  std::cout << "read file: " << fileName.toStdString().c_str() << std::endl;

  QFile file(fileName);

  if (!file.open(QIODevice::ReadOnly))
  {
    std::cout << "could not open file" << std::endl;
    return;
  }

  while (!file.atEnd())
  {
    QString line = file.readLine();
    QStringList numbers = line.split(" ");

    if (numbers.count() < 2)
    {
      std::cout << "stop reading" << std::endl;
      break;
    }

    unsigned int x = QVariant(numbers.at(0)).toUInt();
    unsigned int y = QVariant(numbers.at(1)).toUInt();
    Fling fling(x, y);
    fling.print();
    flings->append(fling);
  }
}
