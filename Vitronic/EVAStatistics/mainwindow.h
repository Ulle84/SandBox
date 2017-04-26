#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDomDocument>
#include <QStringList>
#include <QDateTime>
#include <QList>

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

private slots:
  void checkTimeStampEVAFile();
  void on_actionGenerate_Statistics_triggered();

  void on_actionOpen_EVA_Results_triggered();

  void on_comboBox_currentIndexChanged(const QString& arg1);

  void on_actionReload_EVA_File_triggered();

private:
  bool evaFileLoaded;
  Ui::MainWindow* ui;
  int tableRowCount;
  QDomDocument domDocument;
  QString workingPictureName;
  QStringList outputNames;
  QStringList imageNames;
  QDateTime evaFileLastModified;
  QList<int> versionNumbers;
  QString evaFileName;
  int selectedVersionNumber;
  void processCSVFile(QString filename);
  bool processEVAFile();
  bool reloadEVAFile();
  QString convertHexAsciiToQString(QString HexAscii);
  bool populateTable();
  bool setMemberVariablesToDefault();
};

#endif // MAINWINDOW_H
