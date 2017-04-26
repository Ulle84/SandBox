#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QTime>
class QCalendarWidget;
class QListView;
class QLabel;
class QPushButton;
class QStringListModel;
class QTabWidget;
class QTextEdit;

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    int actTaskNumber;
    bool clockIsRunning;
    QCalendarWidget *analyseCalendar;
    QCalendarWidget *protocolCalendar;
    QDate selectedDate;
    QDateTime startDateTime;
    QLabel *workDirectoryLabel;
    QLabel *taskFileLabel;
    QList<QDateTime> startTimes;
    QList<QDateTime> stopTimes;
    QList<QString> taskDescriptions;
    QList<QString> taskNames;
    QList<QDateTime> analyseStartTimes;
    QList<QDateTime> analyseStopTimes;
    QList<QString> analyseTaskDescriptions;
    QList<QString> analyseTaskNames;
    QListView *analyseListView;
    QListView *effortListView;
    QListView *taskListView;
    QPushButton *chooseDirectoryPushButton;
    QPushButton *chooseFilePushButton;
    QPushButton *stopPushButton;
    QString *stringConfigurationFile;
    QString *workDirectoryString;
    QString *taskFileString;
    QStringList *analyseStringList;
    QStringList *taskStringList;
    QStringList *effortStringList;
    QStringListModel *analyseStringListModel;
    QStringListModel *effortStringListModel;
    QStringListModel *taskStringListModel;
    QTabWidget *tabWidget;
    QTextEdit *summaryTextEdit;
    QTextEdit *taskDescriptionTextEdit;
    QTextEdit *taskDescriptionAnaylseTextEdit;

    bool connectSignalsAndSlots();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    bool chooseDirectory();
    bool chooseTaskFile();
    bool createAnalyse(QDate selectedDate);
    QString createAnalyseString(const int seconds, QString taskString);
    QString createEffortString(int i);
    QString createFileStringFromDate(QDate date);
    bool fileToTaskStringList();
    bool loadAnalyseData();
    bool writeConfiguration();
    bool saveDataToFile();
    bool readConfiguration();
    bool showEffortDetails();
    bool startEffort();
    bool stopEffort();
    bool createAnalyseList();
    bool createEffortList();
    bool loadDataFromFile(QDate date);
    bool fillAnalyseTextBox();
    QString createTimeString(const int seconds);
};

#endif // MAINWINDOW_H
