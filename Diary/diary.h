#ifndef DIARY_H
#define DIARY_H

#include <QtGui/QMainWindow>
#include <QDate>;
class QString; // in den Header nicht den ganzen QtGui Header reinklatschen!
class QTextEdit;
class QCalendarWidget;
class QPushButton;
class QLabel;
class QSpinBox;

class Diary : public QMainWindow
{
  Q_OBJECT

public:
  Diary(QWidget* parent = 0);
  ~Diary();

private slots:
  void goToToday();
  void actualizeEntry(); // Tagebucheintrag aktualisieren
  void saveEntry(); // Tagebucheintrag speichern
  void loadEntry(); // Tagebucheintrag einlesen
  void calendarMonthAndYear(int year, int month);
  void entriesToClipboard();
  void changeEntry01();
  void changeEntry02();
  void changeEntry03();
  void changeEntry04();
  void changeEntry05();
  void changeEntry06();
  QString createFileString();
  // Ordner in denen die Tagebucheinträge sind wechseln

private:
  QDate entryDate; // aktuelles Datum
  QString dateFormat;
  QString directory;
  QString loadedEntry;
  QTextEdit* detailsTextEdit;
  QTextEdit* summaryTextEdit;
  QTextEdit* contactsTextEdit;
  QTextEdit* ideasTextEdit;
  QCalendarWidget* calendarWidget;
  QPushButton* pushButtonToday;
  QPushButton* pushButtonClipboard;
  QPushButton* pushButtonSave;
  QPushButton* pushButton01;
  QPushButton* pushButton02;
  QPushButton* pushButton03;
  QPushButton* pushButton04;
  QPushButton* pushButton05;
  QPushButton* pushButton06;
  QPushButton* pushButton07;
  QPushButton* pushButton08;
  QPushButton* pushButton09;
  QPushButton* pushButton10;
  QSpinBox* anzahlTage;
  QLabel* label;
  QLabel* calendarLabel;
  QAction* actionSave;
  // Speicherort der Tagebucheinträge (Ordner) - oder mache ich das über Ressourcen?
};

#endif // DIARY_H
