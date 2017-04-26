#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSettings;

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  void writeTestFile(const QString& path);

  QByteArray createTestObjectString();

private slots:
  void on_pushButtonWriteTestFile_clicked();

  void on_pushButtonWriteTestOutput_clicked();

private:
    Ui::MainWindow *ui;
    QSettings* m_settings;
};

#endif // MAINWINDOW_H
