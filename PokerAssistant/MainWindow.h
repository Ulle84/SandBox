#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "HandHistory.h"

class QTimer;
class QSettings;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void updateInformation();
  void on_lineEditHandId_textChanged(const QString &arg1);

private:
  Ui::MainWindow *ui;

  QSettings* m_settings;
  HandHistory m_handHistory;
  QTimer* m_timer;
  quint64 m_lastDisplayedHandId;
};

#endif // MAINWINDOW_H
