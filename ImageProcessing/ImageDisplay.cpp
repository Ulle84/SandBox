#include <qmath.h>

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QImage>
#include <QPixmap>
#include <QScrollBar>
#include <QWheelEvent>
#include <QClipboard>

#include "Image.h"
#include "GeometryCodeGenerator.h"

#include "ImageDisplay.h"
#include "ui_ImageDisplay.h"

#include "TeachableLine.h"
#include "TeachableRectangle.h"
#include "TeachableCirlce.h"
#include "TeachableRectangleRotated.h"
#include "TeachablePolyLine.h"

ImageDisplay::ImageDisplay(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ImageDisplay),
  m_ctrlButtonIsPressed(false),
  m_image(0),
  m_penOutlines(QPen(QColor(255, 0, 0))),
  m_penTeachinPoints(QPen(QColor(0, 255, 0))),
  m_brush(QBrush()),
  m_currentTeachingPoint(NULL),
  m_currentTeachable(NULL)
{
  ui->setupUi(this);

  ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  ui->graphicsView->setBackgroundBrush(QBrush(QColor(Qt::gray)));
  ui->graphicsView->show();

  m_scene = new QGraphicsScene();
  ui->graphicsView->setScene(m_scene);

  ui->graphicsView->installEventFilter(this);
  ui->graphicsView->scene()->installEventFilter(this);
  ui->graphicsView->verticalScrollBar()->installEventFilter(this);
  ui->graphicsView->horizontalScrollBar()->installEventFilter(this);
}

ImageDisplay::~ImageDisplay()
{
  delete m_scene;
  delete ui;
}

bool ImageDisplay::eventFilter(QObject *target, QEvent *event)
{
  if (target == ui->graphicsView->scene())
  {
    QGraphicsSceneMouseEvent* mouseEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);

    bool teachButtonChecked = ui->toolButtonTeachLine->isChecked() || ui->toolButtonTeachRectangle->isChecked() || ui->toolButtonTeachCircle->isChecked() || ui->toolButtonTeachRotatedRectangle->isChecked() || ui->toolButtonTeachPolyLine->isChecked();

    if (event->type() == QEvent::GraphicsSceneMouseMove)
    {
      if (mouseEvent)
      {
        m_mouseMovePosition = mouseEvent->scenePos();
      }

      int x = qRound(m_mouseMovePosition.x());
      int y = qRound(m_mouseMovePosition.y());

      QString pixelInformation;

      if (m_image)
      {
        unsigned int qtyLayers = m_image->getQtyLayers();

        if (qtyLayers == 1)
        {
          pixelInformation = tr("gray value: %1").arg(m_image->getValue(x, y));
        }
        else if (qtyLayers == 3 || qtyLayers == 4)
        {
          pixelInformation = tr("red: %1  green: %2  blue: %3").arg(m_image->getValue(x, y, 0)).arg(m_image->getValue(x, y, 1)).arg(m_image->getValue(x, y, 2));

          if (qtyLayers == 4)
          {
            pixelInformation.append(tr("  alpha: %1").arg(m_image->getValue(x, y, 3)));
          }
        }
      }

      ui->label->setText(QString("x: %1  y: %2  %3").arg(x).arg(y).arg(pixelInformation));

      if (m_currentTeachingPoint != NULL)
      {
        m_currentTeachable->positionChanged(m_currentTeachingPoint, m_mouseMovePosition);
        //   notifyTeachables(m_currentTeachingPoint, m_mouseMovePosition);
      }
    }
    else if (event->type() == QEvent::GraphicsSceneMousePress)
    {
      if (mouseEvent)
      {
        m_mousePressPosition = mouseEvent->scenePos();
      }

      if (teachButtonChecked)
      {
        if (m_currentTeachable != NULL)
        {
          m_currentTeachable->setTeachingPointsVisible(false);
        }

        if (ui->toolButtonTeachLine->isChecked())
        {
          QGraphicsLineItem* lineItem = m_scene->addLine(QLineF(m_mousePressPosition, m_mousePressPosition), m_penOutlines);
          m_currentTeachable = new TeachableLine(lineItem, m_scene, &m_penTeachinPoints);
        }
        else if (ui->toolButtonTeachRectangle->isChecked())
        {
          QGraphicsRectItem* rectItem = m_scene->addRect(QRectF(m_mousePressPosition, m_mousePressPosition), m_penOutlines, m_brush);
          m_currentTeachable = new TeachableRectangle(rectItem, m_scene, &m_penTeachinPoints);
        }
        else if (ui->toolButtonTeachCircle->isChecked())
        {
          QGraphicsEllipseItem* ellipseItem = m_scene->addEllipse(QRectF(m_mousePressPosition, m_mousePressPosition), m_penOutlines, m_brush);
          m_currentTeachable = new TeachableCirlce(ellipseItem, m_scene, &m_penTeachinPoints);
        }
        else if (ui->toolButtonTeachRotatedRectangle->isChecked())
        {
          RectangleRotated* rectangleRotated = new RectangleRotated(&m_penOutlines, &m_brush);

          Rectangle rect;
          rect.setX(m_mousePressPosition.x());
          rect.setY(m_mousePressPosition.y());
          rect.setWidth(1);
          rect.setHeight(1);
          rectangleRotated->setRectangle(rect);

          m_scene->addItem(rectangleRotated);
          m_currentTeachable = new TeachableRectangleRotated(rectangleRotated, m_scene, &m_penTeachinPoints);
        }
        else if (ui->toolButtonTeachPolyLine->isChecked())
        {
          GraphicsPolyLineItem* graphicsPolyLineItem = new GraphicsPolyLineItem(&m_penOutlines, &m_brush);

          PolyLine polyLine;
          /*polyLine.push_back(Point(10, 10));
          polyLine.push_back(Point(10, 20));
          polyLine.push_back(Point(20, 20));*/
          polyLine.push_back(Point(Converter::toPoint(m_mousePressPosition)));
          polyLine.push_back(Point(Converter::toPoint(m_mousePressPosition)));
          graphicsPolyLineItem->setPolyLine(polyLine);

          m_scene->addItem(graphicsPolyLineItem);
          m_currentTeachable = new TeachablePolyLine(graphicsPolyLineItem, m_scene, &m_penTeachinPoints);
        }

        m_teachables.append(m_currentTeachable);
        m_currentTeachingPoint = m_currentTeachable->defaultTeachingPoint();
      }
      else if (!ui->toolButtonDragImage->isChecked())
      {
        QGraphicsItem* item = m_scene->itemAt(m_mouseMovePosition, ui->graphicsView->transform());

        for (auto it = m_teachables.begin(); it != m_teachables.end(); it++)
        {
          if ((*it)->hasGraphicsItem(item))
          {
            if (m_currentTeachable != *it)
            {
              if (m_currentTeachable != NULL)
              {
                m_currentTeachable->setTeachingPointsVisible(false);
              }

              m_currentTeachable = *it;
              m_currentTeachable->setTeachingPointsVisible(true);
            }
            break;
          }
        }

        if (item->type() == QGraphicsLineItem::Type)
        {
          QGraphicsLineItem* lineItem = dynamic_cast<QGraphicsLineItem*>(item);

          if (lineItem)
          {
            ui->lineEditCode->setText(GeometryCodeGenerator::generate(lineItem->line()));
          }
        }
        else if (item->type() == QGraphicsRectItem::Type)
        {
          QGraphicsRectItem* rectItem = dynamic_cast<QGraphicsRectItem*>(item);

          if (rectItem)
          {
            ui->lineEditCode->setText(GeometryCodeGenerator::generate(rectItem->rect()));
          }
        }
        else if (item->type() == RectangleRotated::Type)
        {
          RectangleRotated* rectangleRotated = dynamic_cast<RectangleRotated*>(item);

          if (rectangleRotated)
          {
            ui->lineEditCode->setText("ToDo");
          }
        }
        else if (item->type() == QGraphicsEllipseItem::Type)
        {
          QGraphicsEllipseItem* ellipseItem = dynamic_cast<QGraphicsEllipseItem*>(item);

          if (ellipseItem)
          {
            bool ellipseIsTeachingPoint = false;
            for (auto it = m_teachables.begin(); it != m_teachables.end(); it++)
            {
              if ((*it)->hasTeachingPoint(ellipseItem))
              {
                ellipseIsTeachingPoint = true;
                m_currentTeachingPoint = ellipseItem;
                m_currentTeachable = *it;
                m_currentTeachable->setTeachingPointsVisible(false);
                break;
              }
            }

            if (!ellipseIsTeachingPoint)
            {
              m_currentTeachingPoint = NULL;
              ui->lineEditCode->setText(GeometryCodeGenerator::generate(ellipseItem->rect(), true, true));
            }
          }
        }
        else
        {
          if (m_currentTeachable != NULL)
          {
            m_currentTeachable->setTeachingPointsVisible(false);
            m_currentTeachable = NULL;
          }
          ui->lineEditCode->clear();
        }
      }
    }
    else if (event->type() == QEvent::GraphicsSceneMouseRelease)
    {
      m_currentTeachingPoint = NULL;
      resetControls();

      if (m_currentTeachable != NULL)
      {
        m_currentTeachable->setTeachingPointsVisible(true);
      }
    }
  }

  // zoom
  if (target == ui->graphicsView || target == ui->graphicsView->verticalScrollBar() || target == ui->graphicsView->horizontalScrollBar())
  {
    if (event->type() == QEvent::KeyPress)
    {
      QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

      if (keyEvent->key() == Qt::Key_Control)
      {
        m_ctrlButtonIsPressed = true;
      }
    }
    else if (event->type() == QEvent::KeyRelease)
    {
      QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

      if (keyEvent->key() == Qt::Key_Control)
      {
        m_ctrlButtonIsPressed = false;
      }
    }
    else if (event->type() == QEvent::Wheel && m_ctrlButtonIsPressed)
    {
      QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);

      qreal factor = qPow(1.2, wheelEvent->delta() / 240.0);
      ui->graphicsView->scale(factor, factor);
      return true;
    }
  }

  return QWidget::eventFilter(target, event);
}

void ImageDisplay::setImage(Image* image)
{
  m_image = image;

  const unsigned char* data = m_image->getLayer(0);
  QImage::Format format = QImage::Format_Indexed8;

  if (image->getQtyLayers() == 3)
  {
    std::vector<unsigned int> layerIndices;
    layerIndices.push_back(2);
    layerIndices.push_back(1);
    layerIndices.push_back(0);
    layerIndices.push_back(0);
    data = m_image->getSingleLayer(layerIndices);
    format = QImage::Format_RGB32;
  }

  if (image->getQtyLayers() == 4)
  {
    std::vector<unsigned int> layerIndices;
    layerIndices.push_back(2);
    layerIndices.push_back(1);
    layerIndices.push_back(0);
    layerIndices.push_back(3);
    data = m_image->getSingleLayer(layerIndices);
    format = QImage::Format_ARGB32;
  }

  QImage qImage(data, image->getWidth(), image->getHeight(), format);
  QPixmap pixmap = QPixmap::fromImage(qImage);

  m_scene->clear();
  m_scene->addPixmap(pixmap);

  ui->graphicsView->setScene(m_scene);

  //ui->graphicsView->fitInView( m_scene->sceneRect(), Qt::KeepAspectRatio );
}

void ImageDisplay::on_pushButtonZoomIn_clicked()
{
  ui->graphicsView->scale(1.25, 1.25);
}

void ImageDisplay::on_pushButtonZoomOut_clicked()
{
  ui->graphicsView->scale(0.8, 0.8);
}

void ImageDisplay::on_pushButtonClipboard_clicked()
{
  QApplication::clipboard()->setText(ui->lineEditCode->text());
}

void ImageDisplay::on_toolButtonDragImage_clicked(bool checked)
{
  if (checked)
  {
    resetControls();
    ui->toolButtonDragImage->setChecked(true);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
  }
  else
  {
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
  }
}

void ImageDisplay::on_toolButtonTeachLine_clicked(bool checked)
{
  if (checked)
  {
    resetControls();
    ui->toolButtonTeachLine->setChecked(true);
  }
}

void ImageDisplay::on_toolButtonTeachRectangle_clicked(bool checked)
{
  if (checked)
  {
    resetControls();
    ui->toolButtonTeachRectangle->setChecked(true);
  }
}

void ImageDisplay::on_toolButtonTeachCircle_clicked(bool checked)
{
  if (checked)
  {
    resetControls();
    ui->toolButtonTeachCircle->setChecked(true);
  }
}

void ImageDisplay::on_toolButtonTeachRotatedRectangle_clicked(bool checked)
{
  if (checked)
  {
    resetControls();
    ui->toolButtonTeachRotatedRectangle->setChecked(true);
  }
}

void ImageDisplay::resetControls()
{
  ui->toolButtonDragImage->setChecked(false);
  ui->toolButtonTeachLine->setChecked(false);
  ui->toolButtonTeachRectangle->setChecked(false);
  ui->toolButtonTeachCircle->setChecked(false);
  ui->toolButtonTeachRotatedRectangle->setChecked(false);
  ui->toolButtonTeachPolyLine->setChecked(false);
  ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
}

void ImageDisplay::on_toolButtonTeachPolyLine_clicked(bool checked)
{
  if (checked)
  {
    resetControls();
    ui->toolButtonTeachPolyLine->setChecked(true);
  }
}
