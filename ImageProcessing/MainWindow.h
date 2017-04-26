#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSettings;

class Image;
class ImageDisplay;

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
  void on_actionOpenImage_triggered();

private:
  void imageTest();
  void histogramTest();
  void polarTransformationTest();
  void filterTest();
  void binomialFilterTest();
  void morphologyTest();
  void polyLineTest();
  void edgeDetectionTest();
  void lineDirectionTest();
  void statisticsTest();
  void rotatedRectangleTest();
  void setLineTest();
  void setStructuringElementTest();
  void showLena();
  void openAndShowImage(const QString& fileName, bool provideFeedback = false);

  Ui::MainWindow* ui;
  Image* m_image;
  ImageDisplay* m_imageDisplay;

  QString m_lastSelectedFile;
  QSettings* m_settings;
};

#endif // MAINWINDOW_H
