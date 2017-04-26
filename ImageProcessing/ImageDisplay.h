#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include <QBrush>
#include <QWidget>
#include <QGraphicsScene>
#include <QLine>
#include <QPoint>
#include <QRect>
#include <QGraphicsLineItem>
#include <QVector>
#include <QPair>

class Image;
class Teachable;

namespace Ui {
class ImageDisplay;
}

class ImageDisplay : public QWidget
{
  Q_OBJECT

public:
  explicit ImageDisplay(QWidget *parent = 0);
  ~ImageDisplay();
  
  bool eventFilter(QObject *target, QEvent *event);
  void setImage(Image* image);

private slots:
  void on_pushButtonZoomIn_clicked();
  void on_pushButtonZoomOut_clicked();
  void on_pushButtonClipboard_clicked();

  void on_toolButtonDragImage_clicked(bool checked);
  void on_toolButtonTeachLine_clicked(bool checked);
  void on_toolButtonTeachRectangle_clicked(bool checked);
  void on_toolButtonTeachCircle_clicked(bool checked);

  void on_toolButtonTeachRotatedRectangle_clicked(bool checked);

  void on_toolButtonTeachPolyLine_clicked(bool checked);

private:
  void resetControls();

  Ui::ImageDisplay *ui;
  QGraphicsScene* m_scene;
  bool m_ctrlButtonIsPressed;
  Image* m_image;

  QPointF m_mousePressPosition;
  QPointF m_mouseMovePosition;

  QGraphicsEllipseItem* m_currentTeachingPoint;

  QList<Teachable*> m_teachables; // TODO clear list and delete entrys
  Teachable* m_currentTeachable;

  QPen m_penOutlines;
  QPen m_penTeachinPoints;
  QBrush m_brush;
};

#endif // IMAGEDISPLAY_H
