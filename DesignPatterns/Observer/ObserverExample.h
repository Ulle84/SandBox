#ifndef OBSERVEREXAMPLE_H
#define OBSERVEREXAMPLE_H

#include <QMainWindow>
#include <QString>

class Subject;
class IObserver;

namespace Ui {
class ObserverExample;
}

class ObserverExample : public QMainWindow
{
  Q_OBJECT

public:
  explicit ObserverExample(QWidget *parent = 0);
  ~ObserverExample();

private slots:
  void on_pushButtonNotifyObservers_clicked();
  void on_pushButtonConnectA_clicked();
  void on_pushButtonDisconnectA_clicked();
  void on_pushButtonConnectB_clicked();
  void on_pushButtonDisconnectB_clicked();

private:
  Ui::ObserverExample *ui;
  Subject* mSubject;
  IObserver* mObserverA;
  IObserver* mObserverB;
};

#endif // OBSERVEREXAMPLE_H
