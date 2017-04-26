#ifndef ZUGABFAHRT_H
#define ZUGABFAHRT_H

#include <QtGui/QWidget>

// Vorwärtsdeklaration der verwendeten Klassen - nicht den ganzen Header reinklatschen, das wäre schlechter Programmierstil
class QLabel;
class QPushButton;
class QString;
class QStringList;

class Zugabfahrt : public QWidget
{
    Q_OBJECT

private:
    int intFahrzeit;
    QLabel *labelAktuelleZeit;
    QLabel *labelNaechsterZug;
    QPushButton *pushButtonTestSound;
    QString *stringConfigurationFile;
    QStringList *stringListAbfahrtszeiten;
    QStringList *stringListAbfahrtszeitenUserInput;

public:
    Zugabfahrt(QWidget *parent = 0);
    ~Zugabfahrt();

private slots:
    void changeFahrzeit(int newValue);
    void checkTimetable();
    void informUser();
    void writeConfiguration();
    void readConfiguration();
    void createStringListAbfahrtszeiten();
};

#endif // ZUGABFAHRT_H
