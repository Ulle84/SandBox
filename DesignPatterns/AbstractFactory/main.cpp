#include <QDebug>
#include <QString>

#include "ConcreteFactory1.h"
#include "ConcreteFactory2.h"

int main(int argc, char *argv[])
{
  ConcreteFactory1 cf1;
  AbstractProductAI* productA1 = cf1.createProductA();
  AbstractProductBI* productB1 = cf1.createProductB();

  ConcreteFactory2 cf2;
  AbstractProductAI* productA2 = cf2.createProductA();
  AbstractProductBI* productB2 = cf2.createProductB();

  qDebug() << "description of productA1" << QString::fromStdString(productA1->getDescription());
  qDebug() << "description of productB1" << QString::fromStdString(productB1->getDescription());
  qDebug() << "description of productA2" << QString::fromStdString(productA2->getDescription());
  qDebug() << "description of productB2" << QString::fromStdString(productB2->getDescription());

  delete productA1;
  delete productB1;
  delete productA2;
  delete productB2;

  return 0;
}
