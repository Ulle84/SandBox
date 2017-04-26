#ifndef MDIAREABACKGROUND_H
#define MDIAREABACKGROUND_H

#include <QMdiArea>
#include <QPixmap>

class MdiAreaBackground : public QMdiArea
{
public:
  MdiAreaBackground(const QString& pathToPixmap, QWidget *parent = 0);

protected:
  void paintEvent(QPaintEvent *event);

private:
  QPixmap m_pixmap;
};

#endif // MDIAREABACKGROUND_H
