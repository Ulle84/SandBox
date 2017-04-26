#include <QCoreApplication>
#include <QDebug>

#include "BurgerKing.h"
#include "MacDonald.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  BurgerShopI* burgerShop = new MacDonald();
  CheeseburgerI* cheeseburger = burgerShop->createCheeseburger();
  FriesI* fries = burgerShop->createFries();

  qDebug() << cheeseburger->getPrice();

  delete cheeseburger;
  delete fries;
  delete burgerShop;

  return a.exec();
}
