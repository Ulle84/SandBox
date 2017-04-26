#include "zugabfahrt.h"
#include <iostream>

#include <QtGui>

Zugabfahrt::Zugabfahrt(QWidget *parent)
    : QWidget(parent)
{
    // Initialisierung
    stringConfigurationFile = new QString("configuration.dat");
    readConfiguration();

    stringListAbfahrtszeiten = new QStringList();
    stringListAbfahrtszeitenUserInput = new QStringList(); //ToDo Liste variabel erstellen (Textfile, QListWidget)
    stringListAbfahrtszeitenUserInput->append("14:20");
    stringListAbfahrtszeitenUserInput->append("14:50");
    stringListAbfahrtszeitenUserInput->append("15:20");
    stringListAbfahrtszeitenUserInput->append("15:50");
    stringListAbfahrtszeitenUserInput->append("16:20");
    stringListAbfahrtszeitenUserInput->append("16:50");
    stringListAbfahrtszeitenUserInput->append("17:20");
    stringListAbfahrtszeitenUserInput->append("17:50");
    stringListAbfahrtszeitenUserInput->append("18:20");
    stringListAbfahrtszeitenUserInput->append("18:50");
    stringListAbfahrtszeitenUserInput->append("19:20");
    stringListAbfahrtszeitenUserInput->append("19:50");
    stringListAbfahrtszeitenUserInput->append("20:20");
    stringListAbfahrtszeitenUserInput->append("20:50");
    stringListAbfahrtszeitenUserInput->append("21:20");
    stringListAbfahrtszeitenUserInput->append("21:50");
    stringListAbfahrtszeitenUserInput->append("22:20");
    stringListAbfahrtszeitenUserInput->append("22:50");
    stringListAbfahrtszeitenUserInput->append("23:20");
    stringListAbfahrtszeitenUserInput->append("23:50");


    // Initalisierung der Klassen-GUI-Komponenten
    labelAktuelleZeit = new QLabel();
    labelNaechsterZug = new QLabel();
    pushButtonTestSound = new QPushButton(tr("Test Sound"));

    // Initalisierung der GUI-Komponenten
    QGridLayout *gridLayout01 = new QGridLayout();
    QLabel *label01 = new QLabel(tr("Fahrzeit in Minuten: "));
    QSpinBox *spinBox01 = new QSpinBox();
    QVBoxLayout *vBoxLayout01 = new QVBoxLayout();

    // Anpassen der GUI-Komponenten
    labelAktuelleZeit->setAlignment(Qt::AlignHCenter);
    labelNaechsterZug->setAlignment(Qt::AlignHCenter);
    spinBox01->setValue(intFahrzeit);

    // Zusammensammenstellung der Widgets
    gridLayout01->addWidget(label01, 0, 0);
    gridLayout01->addWidget(spinBox01, 0, 1);
    vBoxLayout01->addWidget(labelAktuelleZeit);
    vBoxLayout01->addWidget(labelNaechsterZug);
    vBoxLayout01->addLayout(gridLayout01);
    vBoxLayout01->addWidget(pushButtonTestSound);
    setLayout(vBoxLayout01);

    // Zeitanzeige
    QTimer *timer = new QTimer(this);
    timer->start(1000); // alle x Millisekunden wird das Signal timeout() gesendet

    // Connections between Signals and Slots
    connect(timer, SIGNAL(timeout()), this, SLOT(checkTimetable()));
    connect(pushButtonTestSound, SIGNAL(clicked()), this, SLOT(informUser()));
    connect(spinBox01, SIGNAL(valueChanged(int)), this, SLOT(changeFahrzeit(int)));

    // Funktionsaufrufe
    createStringListAbfahrtszeiten();
    checkTimetable(); // damit beim Programmstart gleich was angezeigt wird
}

Zugabfahrt::~Zugabfahrt() {
    writeConfiguration();
}

void Zugabfahrt::checkTimetable() {
    QTime time = QTime::currentTime();
    labelAktuelleZeit->setText(time.toString("hh:mm:ss"));

    if (time.addSecs(intFahrzeit * 60).toString("hh:mm") == stringListAbfahrtszeiten->first()) {
        labelNaechsterZug->setText(tr("Naechster Zug faehrt um ") + stringListAbfahrtszeiten->first());
        stringListAbfahrtszeiten->removeFirst();
        informUser();
    }
}

void Zugabfahrt::informUser() {
#ifdef Q_WS_MAC
    QApplication::beep();
#endif
#ifdef Q_WS_WIN
    QSound::play("c:/WINDOWS/Media/chimes.wav");
#endif
    QApplication::alert(this, 0);
}

void Zugabfahrt::changeFahrzeit(int newValue) {
    intFahrzeit = newValue;
    createStringListAbfahrtszeiten();
}

void Zugabfahrt::writeConfiguration() {
    //QString directory = QDir::homePath();
    QFile file(*stringConfigurationFile);
    if (!file.open(QIODevice::WriteOnly)) {
        std::cerr << "Cannot open file for writing: " << qPrintable(file.errorString()) << std::endl;
        return;
    }
    QDataStream out (&file);
    out.setVersion(QDataStream::Qt_4_6);

    out << quint32(intFahrzeit);
}

void Zugabfahrt::readConfiguration() {
    QFile file(*stringConfigurationFile);
    if (!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Cannot open file for reading: " << qPrintable(file.errorString()) << std::endl;
        intFahrzeit = 10; // Standard-Wert
        return;
    }
    QDataStream in (&file);
    in.setVersion(QDataStream::Qt_4_6);

    in >> intFahrzeit;
}

void Zugabfahrt::createStringListAbfahrtszeiten() {
    stringListAbfahrtszeiten->clear();
    labelNaechsterZug->clear();
    QTime time = QTime::currentTime().addSecs(60 * intFahrzeit);
    QString stringTime = time.toString("hh:mm");
    stringListAbfahrtszeitenUserInput->sort();
    for (int i = 0; i < stringListAbfahrtszeitenUserInput->length(); i++) {
        if (stringListAbfahrtszeitenUserInput->at(i) > stringTime) {
            if (!stringListAbfahrtszeiten->contains(stringListAbfahrtszeitenUserInput->at(i))) {
                stringListAbfahrtszeiten->append(stringListAbfahrtszeitenUserInput->at(i));
            }
        }
    }
}
