#include <QDebug>

#include "ObserverExample.h"
#include "ui_ObserverExample.h"
#include "ObserverA.h"
#include "ObserverB.h"
#include "Subject.h"

ObserverExample::ObserverExample(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::ObserverExample)
{
  ui->setupUi(this);

  mSubject = new Subject();
  mObserverA = new ObserverA();
  mObserverB = new ObserverB();
}

ObserverExample::~ObserverExample()
{
  mSubject->unregisterObserver(mObserverA);
  mSubject->unregisterObserver(mObserverB);
  delete mObserverB;
  delete mObserverA;
  delete mSubject;
  delete ui;
}

void ObserverExample::on_pushButtonNotifyObservers_clicked()
{
  qDebug() << "-----------------------------";
  qDebug() << "notifyObservers";
  mSubject->notifyObservers();
}

void ObserverExample::on_pushButtonConnectA_clicked()
{
    mSubject->registerObserver(mObserverA);
}

void ObserverExample::on_pushButtonDisconnectA_clicked()
{
    mSubject->unregisterObserver(mObserverA);
}

void ObserverExample::on_pushButtonConnectB_clicked()
{
    mSubject->registerObserver(mObserverB);
}

void ObserverExample::on_pushButtonDisconnectB_clicked()
{
    mSubject->unregisterObserver(mObserverB);
}
