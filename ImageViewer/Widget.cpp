/* TODO
 - pause-function via spacebar or UI-Contorl
*/

#include "Widget.h"
#include "ui_Widget.h"

#include <qmath.h>

#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <QFileDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    currentIndex(0)
{
    qsrand(QDateTime::currentDateTime().toTime_t());

    ui->setupUi(this);

    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->setBackgroundBrush(QBrush(QColor(Qt::black)));
    ui->graphicsView->show();

    parseBaseFolder();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showImage()));
    timer->start(2000);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->graphicsView->viewport())
    {
        if (event->type() == QEvent::Wheel)
        {
            QWheelEvent *wheelEvent = static_cast<QWheelEvent *> (event);

            qreal factor = qPow(1.2, wheelEvent->delta() / 240.0);
            ui->graphicsView->scale(factor, factor);
            //ui->graphicsView->rotate(factor);
            //event->accept();
            return true;
        }

    }
    return false;
}

void Widget::parseBaseFolder()
{
    QString directory = QFileDialog::getExistingDirectory();

    if (directory.isEmpty())
    {
        return;
    }

    QDirIterator it(directory, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QString fileName = it.next();
        if (fileName.endsWith(".jpg", Qt::CaseInsensitive))
        {
            imagePaths.append(fileName);
        }
    }
}

void Widget::showImage()
{
    if (ui->checkBoxRandom->isChecked())
    {
        currentIndex = qrand() % imagePaths.length();
    }
    else
    {
        QString currentPath = imagePaths.at(currentIndex);
        QString currentBasePath = currentPath.left(currentPath.lastIndexOf("/"));

        currentIndex++;
        if (currentIndex > imagePaths.length())
        {
            currentIndex = 0;
        }

        if (ui->checkBoxCycle->isChecked())
        {

            QString nextPath = imagePaths.at(currentIndex);
            QString nextBasePath = nextPath.left(currentPath.lastIndexOf("/"));

            if (currentBasePath != nextBasePath)
            {
                // jump to first image in folder
                currentIndex--;
                while (imagePaths.at(currentIndex - 1).left(imagePaths.at(currentIndex - 1).lastIndexOf("/")) == currentBasePath)
                {
                    currentIndex--;
                }
            }

        }
    }

    ui->labelPath->setText(imagePaths.at(currentIndex));

    QImage img(imagePaths.at(currentIndex));

    QGraphicsScene* scene = new QGraphicsScene();
    QPixmap pixmap = QPixmap::fromImage(img);

    scene->addPixmap(pixmap);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
}

void Widget::on_spinBox_valueChanged(int interval)
{
    timer->stop();
    timer->start(interval);
}

void Widget::on_checkBoxRandom_stateChanged(int state)
{
    ui->checkBoxCycle->setEnabled(state == Qt::Unchecked);
}
