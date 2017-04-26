#include <QDebug>
#include <QPainter>

#include "MdiAreaBackground.h"

MdiAreaBackground::MdiAreaBackground(const QString& pathToPixmap, QWidget *parent) :
  QMdiArea(parent),
  m_pixmap(pathToPixmap)
{
  setBackground(QBrush(QColor(255, 255, 255)));
}

void MdiAreaBackground::paintEvent(QPaintEvent* event)
{
  QMdiArea::paintEvent(event);

  QPainter painter(viewport());
  painter.setOpacity(0.3);

  // Calculate the logo position - the bottom right corner of the mdi area.

  QPixmap scaled = m_pixmap.scaledToWidth(width() * 0.6);

  int x = width() * 0.2;
  int y = height() / 2 - scaled.height() / 2;

  // centered
  /*int x = width() / 2 - m_pixmap.width() / 2;
  int y = height() / 2 - m_pixmap.height() / 2;*/
  painter.drawPixmap(x, y, scaled);
}
