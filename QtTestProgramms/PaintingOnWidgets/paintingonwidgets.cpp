#include <QPainter>
#include <QPicture>
#include <QPainterPath>
#include <QImage>
#include <QString>
#include <QFileDialog>
#include <iostream>
#include "paintingonwidgets.h"

PaintingOnWidgets::PaintingOnWidgets(QWidget *parent)
    : QWidget(parent)
{
}

PaintingOnWidgets::~PaintingOnWidgets()
{
    
}

void PaintingOnWidgets::paintEvent(QPaintEvent *)
{
  QPainter painter (this);
  painter.drawRect(0, 0, 100, 200);
  painter.drawText(10, 20, "hello World");
  painter.fillRect(100, 100, 100, 100, Qt::Dense5Pattern);
  painter.drawEllipse(300, 300, 200, 100);

  // image content
  int height = 256;
  int width = 256;
  int size = height * width;
  unsigned char* pic = new unsigned char [size];
  for (int i = 0; i < size; i++) {
      pic[i] = i % 256;
  }
  QImage image(pic, width, height, QImage::Format_Indexed8);

  QPicture picture;
  QString fileName = "E:\\h_da\\BPS\\Unterschrift.bmp"; //QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath());
  bool pictureLoaded = picture.load(fileName);
  if (pictureLoaded)
    painter.drawPicture(100, 0, picture);
  else
      std::cout << "picture not loaded" << std::endl;

  QPainterPath path;
  path.moveTo(20, 80);
  path.lineTo(20, 30);
  path.cubicTo(80, 0, 50, 50, 80, 80);
  painter.drawPath(path);
}

