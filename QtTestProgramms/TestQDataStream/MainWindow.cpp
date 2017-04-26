#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDataStream>
#include <QFile>
#include <QMap>
#include <QVariant>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QVariantMap variantMap;
  QString string = "testString";
  variantMap["test"] = string;

  QVariantMap nestedMap;
  QString nestedString = "nestedString";
  nestedMap["nested"] = nestedString;
  variantMap["nestedTest"] = nestedMap;

  const int length = 256;
  unsigned char* buffer = new unsigned char[length];

  for (int i = 0; i < length; i++)
  {
    buffer[i] = i;
  }

  QFile file("file.dat");
  file.open(QIODevice::WriteOnly);
  QDataStream out(&file);

  out << variantMap;


  out.writeRawData(reinterpret_cast<const char *>(buffer), length);

  file.close();

  file.open(QIODevice::ReadOnly);
  QDataStream in (&file);

  QVariantMap variantMapIn;
  in >> variantMapIn;
  in.readRawData(reinterpret_cast<char *>(buffer), length);

  qDebug() << variantMapIn["test"].toString();
  qDebug() << variantMapIn["nestedTest"].toMap()["nested"].toString();
  qDebug() << "buffer 23:" << static_cast<int>(buffer[23]);

  this->dumpObjectTree();
  this->dumpObjectInfo();

  delete[] buffer;

}

MainWindow::~MainWindow()
{
  delete ui;
}
