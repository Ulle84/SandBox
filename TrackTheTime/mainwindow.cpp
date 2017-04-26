#include "mainwindow.h"
#include <QtGui>

// Bugs

// ToDos
// Speicherung der Daten ändern (Ziel: Dateien sollen lesbar und editierbar sein)
// Sprung von einem Tag auf den anderen abfragen
// Umstellung des Textfiles weiter implementieren
// - Edit-Field für TextFile
// - Edit-Field aktualisieren, sobald sich etwas ändert
// - Edit-Field-Änderungen in interne Variablen übernehmen (speichern und neuladen)
// Auswertung optimieren (es kann jetzt sein, dass in der Datei jüngere vor älteren Einträgen stehen)
// TextBox in der der Inhalt der TaskList gespeichert werden kann

// Ideas
// Dateipfade variabel machen und speichern - Config File
// Details editierbar machen
// Infos mit Versionshistorie
// Programmicon
// Task-ID
// Buttons fürs manuelle Speichern
// Qt Info

// Enhancements
// TaskDesciption uneditable while Clock is not running
// graphics for open file and folder

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // init
    clockIsRunning = false; //ToDo Wert aus config-Datei auslesen
    actTaskNumber = -1;
    taskFileString = new QString("/Users/Ulle/Programmierung/Qt/TrackTheTimeRepo/tasks.txt");
    workDirectoryString = new QString("/Users/Ulle/Programmierung/Qt/TrackTheTimeRepo/");

    stringConfigurationFile = new QString("configuration.dat");
    readConfiguration();

    // init Widgets
    summaryTextEdit = new QTextEdit();
    taskDescriptionAnaylseTextEdit = new QTextEdit();

    // taskList
    taskStringList = new QStringList();
    taskStringListModel = new QStringListModel(this);
    taskListView = new QListView();
    taskListView->setModel(taskStringListModel);
    taskListView->setAlternatingRowColors(true);
    fileToTaskStringList();

    // analyseList
    analyseStringList = new QStringList();
    analyseStringListModel = new QStringListModel(this);
    //analyseStringListModel->setStringList(*analyseStringList);
    analyseListView = new QListView();
    analyseListView->setModel(analyseStringListModel);
    analyseListView->setAlternatingRowColors(true);

    // effortList
    effortStringList = new QStringList();
    effortStringListModel = new QStringListModel(this);
    effortListView = new QListView();
    effortListView->setModel(effortStringListModel);
    effortListView->setAlternatingRowColors(true);
    //loadEffortsFromFile(QDate::currentDate());

    // timeCaptureWidget
    QWidget *timeCaptureWidget = new QWidget;
    taskDescriptionTextEdit = new QTextEdit();
    stopPushButton = new QPushButton(tr("Stop"));
    QVBoxLayout *timeCaptureVBoxLayout = new QVBoxLayout();
    timeCaptureVBoxLayout->addWidget(taskListView);
    timeCaptureVBoxLayout->addWidget(taskDescriptionTextEdit);
    timeCaptureVBoxLayout->addWidget(stopPushButton);
    timeCaptureWidget->setLayout(timeCaptureVBoxLayout);

    // timeAnalyseWidget
    QWidget *timeAnalyseWidget = new QWidget();
    analyseCalendar = new QCalendarWidget();
    analyseCalendar->setFirstDayOfWeek(Qt::Monday);
    QVBoxLayout *timeAnalyseVBoxLayout = new QVBoxLayout();
    //QHBoxLayout *timeAnalyseHBoxLayout = new QHBoxLayout();
    //timeAnalyseHBoxLayout->addStretch();
    //timeAnalyseHBoxLayout->addWidget(analyseCalendar);
    //timeAnalyseHBoxLayout->addStretch();
    timeAnalyseVBoxLayout->addWidget(analyseCalendar);
    timeAnalyseVBoxLayout->addWidget(summaryTextEdit);
    timeAnalyseVBoxLayout->addWidget(analyseListView);
    timeAnalyseVBoxLayout->addWidget(effortListView);
    timeAnalyseVBoxLayout->addWidget(taskDescriptionAnaylseTextEdit);
    timeAnalyseWidget->setLayout(timeAnalyseVBoxLayout);

    // optionsWidget
    QWidget *optionsWidget = new QWidget;
    taskFileLabel = new QLabel(tr("Aufgabendatei: ") + *taskFileString);
    workDirectoryLabel = new QLabel(tr("Arbeitsverzeichnis: ") + *workDirectoryString);
    //ToDo Matrix-Layout
    chooseFilePushButton = new QPushButton("Wähle Aufgabendatei...");
    chooseDirectoryPushButton = new QPushButton("Wähle Arbeitsverzeichnis...");
    QVBoxLayout *optionsVBoxLayout = new QVBoxLayout();
    optionsVBoxLayout->addWidget(taskFileLabel);
    optionsVBoxLayout->addWidget(chooseFilePushButton);
    optionsVBoxLayout->addWidget(workDirectoryLabel);
    optionsVBoxLayout->addWidget(chooseDirectoryPushButton);
    optionsVBoxLayout->addStretch();
    optionsWidget->setLayout(optionsVBoxLayout);

    // tabWidget
    tabWidget = new QTabWidget();
    tabWidget->addTab(timeCaptureWidget, tr("Zeiterfassung"));
    //tabWidget->addTab(timeProtocolWidget, tr("Protokoll"));
    tabWidget->addTab(timeAnalyseWidget, tr("Analyse"));
    tabWidget->addTab(optionsWidget, tr("Optionen"));
    setCentralWidget(tabWidget);

    connectSignalsAndSlots();
    loadDataFromFile(QDate::currentDate());
    statusBar()->showMessage(tr("Bereit! Aufgabe kann durch Anklicken gestartet werden..."));
}

MainWindow::~MainWindow() {
    stopEffort();
    saveDataToFile();
    writeConfiguration();
}

bool MainWindow::connectSignalsAndSlots() {
    connect(stopPushButton, SIGNAL(clicked()), this, SLOT(stopEffort()));
    connect(taskListView, SIGNAL(clicked(QModelIndex)), this, SLOT(startEffort()));
    connect(chooseFilePushButton, SIGNAL(clicked()), this, SLOT(chooseTaskFile()));
    connect(chooseDirectoryPushButton, SIGNAL(clicked()), this, SLOT(chooseDirectory()));
    connect(analyseCalendar, SIGNAL(clicked(QDate)), this, SLOT(createAnalyse(QDate)));
    connect(effortListView, SIGNAL(clicked(QModelIndex)), this, SLOT(showEffortDetails()));
    return true;
}

bool MainWindow::chooseDirectory() {
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setDirectory(*workDirectoryString);
    //(fileDialog.open();
    QStringList fileNames;
    if (fileDialog.exec()) {
        fileNames = fileDialog.selectedFiles();
    }
    else {
        return false;
    }
    if (fileNames.length() < 1) {
        return false;
    }
    //*workDirectoryString = QFileDialog::getOpenFileName(this, tr("Öffne Aufgabendatei"), QDir::homePath(), ));
    //QFileDialog::ShowDirsOnly setFileMode
    *workDirectoryString = fileNames.at(0);
    workDirectoryLabel->setText(tr("Arbeitsverzeichnis: ") + *workDirectoryString);
    return true;
}

bool MainWindow::chooseTaskFile() {
    QString fileString;
    fileString = QFileDialog::getOpenFileName(this, tr("Öffne Aufgabendatei"), *taskFileString, tr("Aufgabendateien (*.txt)"));
    //ToDo verifizieren, dass nur eine Datei geöffnet werden kann
    if (fileString == "") {
        return false;
    }
    *taskFileString = fileString;
    taskFileLabel->setText(tr("Aufgabendatei: ") + *taskFileString);

    fileToTaskStringList();
    return true;
}

bool MainWindow::createAnalyse(QDate newSelectedDate) {
    taskDescriptionAnaylseTextEdit->clear();
    selectedDate = newSelectedDate;
    loadAnalyseData();
    fillAnalyseTextBox();
    createAnalyseList();
    createEffortList();
    return true;
}

bool MainWindow::fillAnalyseTextBox() {
    summaryTextEdit->clear();
    if (analyseStartTimes.length() == 0) {
        return true;
    }
    int workSeconds = 0;
    for (int i = 0; i < analyseStartTimes.length(); i++) {
        workSeconds += analyseStartTimes.at(i).secsTo(analyseStopTimes.at(i));
    }
    QDateTime firstStartTime = analyseStartTimes.first();
    QDateTime lastStopTime = analyseStopTimes.last();
    int totalSeconds = firstStartTime.secsTo(lastStopTime);
    int pauseSeconds = totalSeconds - workSeconds;
    QString string;
    string.append(tr("Arbeitsbeginn: "));
    string.append(firstStartTime.toString("hh:mm"));
    string.append("\n");
    string.append(tr("Arbeitsende: "));
    string.append(lastStopTime.toString("hh:mm"));
    string.append("\n");
    string.append(tr("Arbeitszeit: "));
    string.append(createTimeString(workSeconds));
    string.append("\n");
    string.append(tr("Pausenzeit: "));
    string.append(createTimeString(pauseSeconds));
    summaryTextEdit->setText(string);
    return true;
}

bool MainWindow::createAnalyseList() {
    analyseStringList->clear();
    analyseStringListModel->setStringList(*analyseStringList);

    QList<QString> taskList;
    QList<int> timeList;
    int seconds;
    if (analyseStartTimes.isEmpty()) { // gibt es nichts zu tun?
        return true;
    }
    for (int i = 0; i < analyseStartTimes.length(); i++) {
        if (!taskList.contains(analyseTaskNames.at(i))) { // ist der String noch nicht in der Liste enhalten?
            taskList.append(analyseTaskNames.at(i));
            timeList.append(0);
        }
        seconds = analyseStartTimes.at(i).secsTo(analyseStopTimes.at(i));
        // getting Index of taskName in taskList
        timeList[taskList.indexOf(analyseTaskNames.at(i))] += seconds;
    }
    for (int i = 0; i < taskList.length(); i++) {
        if (timeList.at(i) >= 60) { // ist mindestens eine Minute "gebucht" worden?
            analyseStringList->append(createAnalyseString(timeList.at(i), taskList.at(i)));
        }
    }
    analyseStringList->sort();
    analyseStringListModel->setStringList(*analyseStringList);
    return true;
}

QString MainWindow::createAnalyseString(const int seconds, QString taskString) {
    QString resultString;
    resultString = createTimeString(seconds);
    resultString.append("   ");
    resultString.append(taskString);
    return resultString;
}

QString MainWindow::createTimeString(const int seconds) {
    int hours;
    int minutes;
    QString resultString;
    hours = seconds/3600;
    minutes = (seconds-hours*3600)/60;
    QTime *time = new QTime(hours, minutes);
    resultString.append(time->toString("hh:mm"));
    return resultString;
}

bool MainWindow::createEffortList() {
    // effortList
    effortStringList->clear();
    effortStringListModel->setStringList(*effortStringList);
    QString string;
    for (int i = 0; i < analyseStartTimes.length(); i++) {
        string = "";
        string.append(analyseStartTimes.at(i).toString("hh:mm"));
        string.append(" - ");
        string.append(analyseStopTimes.at(i).toString("hh:mm"));
        string.append("   ");
        string.append(analyseTaskNames.at(i));
        effortStringList->append(string);
    }
    effortStringListModel->setStringList(*effortStringList);
    return true;
}

QString MainWindow::createEffortString(int i) {
    QString string;
    string.append(startTimes.at(i).toString("hh:mm"));
    string.append(" - ");
    string.append(stopTimes.at(i).toString("hh:mm"));
    string.append("   ");
    string.append(taskNames.at(i));
    return string;
}

QString MainWindow::createFileStringFromDate(QDate date) {
    // ToDo '_newFormat' entfernen, wenn Umstellung in Datenspeicherung abgeschlossen ist
    return QString(*workDirectoryString + date.toString(Qt::ISODate) + ".dat");
}

bool MainWindow::fileToTaskStringList() {
    taskStringList->clear();
    QFile *destFile = new QFile(*taskFileString);
    if (!destFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(destFile);
    while (!in.atEnd()) {
        taskStringList->append(in.readLine());
    }
    taskStringListModel->setStringList(*taskStringList);
    return true;
}

bool MainWindow::loadAnalyseData() {
    analyseStartTimes.clear();
    analyseStopTimes.clear();
    analyseTaskDescriptions.clear();
    analyseTaskNames.clear();
    if (selectedDate == QDate::currentDate()) {
        analyseStartTimes = startTimes;
        analyseStopTimes = stopTimes;
        analyseTaskDescriptions = taskDescriptions;
        analyseTaskNames = taskNames;
    }
    else {
        // leider quick and dirty :-(
        QList<QDateTime> tempStartTimes = startTimes;
        QList<QDateTime> tempStopTimes = stopTimes;
        QList<QString> tempTaskDescriptions = taskDescriptions;
        QList<QString> tempTaskNames = taskNames;

        loadDataFromFile(selectedDate);

        analyseStartTimes = startTimes;
        analyseStopTimes = stopTimes;
        analyseTaskDescriptions = taskDescriptions;
        analyseTaskNames = taskNames;

        startTimes = tempStartTimes;
        stopTimes = tempStopTimes;
        taskDescriptions = tempTaskDescriptions;
        taskNames = tempTaskNames;


        /*
        QFile srcFile(createFileStringFromDate(selectedDate));
        if (!srcFile.open(QIODevice::ReadOnly)) {
            return false;
        }
        QDataStream in (&srcFile);
        in.setVersion(QDataStream::Qt_4_6);
        in >> analyseStartTimes >> analyseStopTimes >> analyseTaskNames >> analyseTaskDescriptions;
        */
    }
    return true;
}

bool MainWindow::loadDataFromFile(QDate date) {
    QFile srcFile(createFileStringFromDate(date));
    if (!srcFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    // ToDo Alle Daten löschen - Funktion schreiben

    //QDataStream in (&srcFile);
    //in.setVersion(QDataStream::Qt_4_6);
    //in >> startTimes >> stopTimes >> taskNames >> taskDescriptions;
    QTextStream in (&srcFile);
    QString line;
    int entryCount = -1;
    QRegExp rx("[0-3]{1,1}[0-9]{1,1}:[0-5]{1,1}[0-9]{1,1} - [0-3]{1,1}[0-9]{1,1}:[0-5]{1,1}[0-9]{1,1}"); // 'hh:mm - hh:mm'
    while (!in.atEnd()) {
        line = in.readLine();

        if (rx.indexIn(line) == 0) {
            entryCount++;
            int startHour = line.mid(0,2).toInt();
            int startMinute = line.mid(3,2).toInt();
            int stopHour = line.mid(8,2).toInt();
            int stopMinute = line.mid(11,2).toInt();

            QDateTime dateTime;
            dateTime.setDate(QDate::currentDate());
            QTime time;
            time.setHMS(startHour, startMinute, 0, 0);
            dateTime.setTime(time);
            startTimes.append(dateTime);
            time.setHMS(stopHour, stopMinute, 0, 0);
            dateTime.setTime(time);
            stopTimes.append(dateTime);
            taskNames.append(in.readLine()); // taskName auslesen
            taskDescriptions.append(""); // dummy
        }
        else {
            if (entryCount >= 0 && line.length() != 0) {
                if (taskDescriptions[entryCount].length() == 0) {
                    taskDescriptions[entryCount] += line;
                }
                else {
                    taskDescriptions[entryCount] += "\n" + line;
                }
            }
        }
    }
    return true;
}

bool MainWindow::writeConfiguration() {
    //QString directory = QDir::homePath();
    QFile file(*stringConfigurationFile);
    if (!file.open(QIODevice::WriteOnly)) {
        //std::cerr << "Cannot open file for writing: " << qPrintable(file.errorString()) << std::endl;
        return false;
    }
    QDataStream out (&file);
    out.setVersion(QDataStream::Qt_4_6);

    out << clockIsRunning << taskFileString << workDirectoryString;
    return true;
}

bool MainWindow::readConfiguration() {
    QFile file(*stringConfigurationFile);
    if (!file.open(QIODevice::ReadOnly)) {
        //std::cerr << "Cannot open file for reading: " << qPrintable(file.errorString()) << std::endl;
        // ToDo Standardwerte eintragen
        //intFahrzeit = 10; // Standard-Wert
        return false;
    }
    QDataStream in (&file);
    in.setVersion(QDataStream::Qt_4_6);

    // ToDo Daten einlesen
    //in >> clockIsRunning >> taskFileString >> workDirectoryString;
    return true;
}

bool MainWindow::saveDataToFile() {
    if (startTimes.length() < 1) {
        return true;
    }
    QFile destFile(createFileStringFromDate(startTimes.at(0).date()));
    if (!destFile.open(QIODevice::WriteOnly)) {
        return false;
    }
    //QDataStream out (&destFile);
    //out.setVersion(QDataStream::Qt_4_6);
    //out << startTimes << stopTimes << taskNames << taskDescriptions;
    QTextStream out (&destFile);
    for (int i = 0; i < startTimes.length(); i++) {
        if (i > 0) {
            out << "\n\n";
        }
        out << startTimes[i].toString("hh:mm") << " - " << stopTimes[i].toString("hh:mm") << "\n";
        out << taskNames[i] << "\n";
        out << taskDescriptions[i];
    }
    return true;
}

bool MainWindow::showEffortDetails() {
    //ToDo Die Funktion auch bei Navigation mit Pfeiltasten ausführen
    int markedRow = effortListView->currentIndex().row(); // markierten Index bekommen
    // beim clicken auf listenitem
    //taskDescriptionProtocolTextEdit->setText(taskDescriptions.at(markedRow));
    taskDescriptionAnaylseTextEdit->setText(analyseTaskDescriptions.at(markedRow));
    return true;
}

bool MainWindow::startEffort() {
    int markedRow = taskListView->currentIndex().row(); // markierten Index bekommen
    if (markedRow == -1) { // ist die Liste noch leer?
        statusBar()->showMessage(tr("Bitte Einträge in Liste anlegen"));
        return false;
    }
    if (clockIsRunning) { // tickt die Uhr schon für eine Aufgabe?
        //if (markedRow == actTaskNumber) { // sind die neue und die aktuelle Aufgabe gleich?
        //    return true;
        //}
        stopEffort();
    }
    // neue Aufgabe
    actTaskNumber = markedRow;
    startDateTime = QDateTime::currentDateTime();  
    clockIsRunning = true;
    statusBar()->showMessage(tr("Aufgabe '%1' um %2 gestartet.").arg(taskStringList->at(taskListView->currentIndex().row())).arg(QTime::currentTime().toString("hh:mm")));
    return true;
}

bool MainWindow::stopEffort() {
    if (!clockIsRunning) {
        return true;
    }
    QDateTime stopDateTime = QDateTime::currentDateTime();
    clockIsRunning = false;
    statusBar()->showMessage(tr("Aufgabe gestoppt."));

    startTimes.append(startDateTime);
    stopTimes.append(stopDateTime);
    taskNames.append(taskStringList->at(actTaskNumber));
    taskDescriptions.append(taskDescriptionTextEdit->toPlainText());
    taskDescriptionTextEdit->clear();

    //effortStringList->append(createEffortString(startTimes.length()-1));
    //effortStringListModel->setStringList(*effortStringList); // "updaten"

    return true;
}
