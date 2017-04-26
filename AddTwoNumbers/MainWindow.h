#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QTimer>
#include "RandomNumberGenerator.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow* ui;
  RandomNumberGenerator* randomNumberGenerator;
  QTimer* timer;
  int correctEnteredValues;
  int wrongEnteredValues;

private slots:
  void showNewRandomNumber();
  void updateStatusBar();
  void on_lineEdit_returnPressed();

};

#endif // MAINWINDOW_H
