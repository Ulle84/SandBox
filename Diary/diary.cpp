#include "diary.h"

#include <QtGui>
#include <QDir>

/*******************************************************************************
ToDos
- Datenverwaltung aufbohren (nicht nur eine Textbox pro Datum sondern Möglichkeit für n Textboxen)
- Layout verändern, textbox höher "gewichten" - soll mehr Platz bekommen, wenn Gesamtfenster größer wird
- Qt Info
- Infodialog mit History im HTML-Style
    - Cmd-S -> speichern des aktuellen Eintrags - geht das mit QAction bei der Vererbung von QWidget?
- anstelle von leerer Datei speichern, Datei löschen

Bugs
    - wenn bei einem existierenden Eintrag alle Zeichen gelöscht werden, wird die Änderung nicht gespeichert, weil das Textfeld auf Länge Null abgefragt wird

Ideen
 - Tage zu denen Einträge existieren rot marikieren- Hintergrundfarben in der Kalenderansicht anpassen
    - Programmicon
    - Button Eintrag löschen
    - Speicherort anzeigen und wechseln (über QDir?) - Einbettung des Speicherorts über Ressourcen
    - verschlüsselte Tagebuchdateien
    - Schriftart über Drop-Down-Menü auswählen
    - Liste aller Einträge
    - AutoSave-Funktion (alle x Sekunden speichern)
    - Summary, Contacts, Ideas, Details
*******************************************************************************/

Diary::Diary(QWidget* parent) : QMainWindow(parent)
{
  // init variables
  dateFormat = "dddd, d. MMMM yyyy";

  // create widgets
  QWidget* centralWidget = new QWidget();
  detailsTextEdit = new QTextEdit();
  summaryTextEdit = new QTextEdit();
  contactsTextEdit = new QTextEdit();
  ideasTextEdit = new QTextEdit();
  detailsTextEdit->setMinimumWidth(700);
  calendarWidget = new QCalendarWidget;
  pushButtonToday = new QPushButton(tr("Heute"));
  label = new QLabel;
  label->setAlignment(Qt::AlignHCenter);
  calendarLabel = new QLabel;
  calendarLabel->setAlignment(Qt::AlignHCenter);
  pushButtonClipboard = new QPushButton(tr("Eintrag in Zwischenablage"));
  pushButtonSave = new QPushButton(tr("Eintrag speichern"));
  pushButton01 = new QPushButton("<<<");
  pushButton02 = new QPushButton("<<");
  pushButton03 = new QPushButton("<");
  pushButton04 = new QPushButton(">");
  pushButton05 = new QPushButton(">>");
  pushButton06 = new QPushButton(">>>");
  //pushButton07 = new QPushButton("<<");
  //pushButton08 = new QPushButton("<");
  //pushButton09 = new QPushButton(">");
  //pushButton10 = new QPushButton(">>");
  actionSave = new QAction(tr("&Save"), this);
  actionSave->setShortcut(QKeySequence::Save);
  detailsTextEdit->addAction(actionSave);

  // init widgets
  anzahlTage = new QSpinBox();
  anzahlTage->setMinimum(1);
  anzahlTage->setMaximum(100);
  calendarWidget->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
  calendarWidget->setFirstDayOfWeek(Qt::Monday);
  //calendarWidget->setNavigationBarVisible(false);

  QTextCharFormat format;
  format.setForeground(QColor(0, 0, 0));
  calendarWidget->setWeekdayTextFormat(Qt::Saturday, format);
  calendarWidget->setWeekdayTextFormat(Qt::Sunday, format);

  // today in red
  QDate date = QDate::currentDate();
  QTextCharFormat textCharFormat;
  textCharFormat.setForeground(Qt::red);
  calendarWidget->setDateTextFormat(date, textCharFormat);


  // damit Kalender nicht übergroß gezeichnet wird
  //calendarWidget->setMaximumHeight(180); // standard: 145
  //calendarWidget->setMaximumWidth(300); // standard: 272

  //QTabWidget *tabWidget = new QTabWidget();
  //tabWidget->addTab(detailsTextEdit, tr("Details"));
  //tabWidget->addTab(summaryTextEdit, tr("Zusammenfassung"));
  //tabWidget->addTab(contactsTextEdit, tr("Kontakte"));
  //tabWidget->addTab(ideasTextEdit, tr("Ideen"));

  QHBoxLayout* buttons = new QHBoxLayout;
  buttons->addWidget(pushButton01);
  buttons->addWidget(pushButton02);
  buttons->addWidget(pushButton03);
  buttons->addWidget(pushButtonToday);
  buttons->addWidget(pushButton04);
  buttons->addWidget(pushButton05);
  buttons->addWidget(pushButton06);

  //QHBoxLayout *buttons2 = new QHBoxLayout;
  //buttons2->addWidget(pushButton07);
  //buttons2->addWidget(pushButton08);
  //buttons2->addWidget(pushButton09);
  //buttons2->addWidget(pushButton10);

  QHBoxLayout* buttons3 = new QHBoxLayout;
  buttons3->addWidget(anzahlTage);
  buttons3->addWidget(pushButtonClipboard);
  buttons3->addWidget(pushButtonSave);

  QHBoxLayout* layoutCalendar = new QHBoxLayout;
  //layoutCalendar->addStretch();
  layoutCalendar->addWidget(calendarWidget);
  //layoutCalendar->addStretch();

  QVBoxLayout* leftLayout = new QVBoxLayout;
  //leftLayout->addWidget(calendarLabel);
  leftLayout->addLayout(layoutCalendar);
  //leftLayout->addLayout(buttons2);
  //leftLayout->addWidget(pushButtonToday);
  leftLayout->addStretch();
  leftLayout->addLayout(buttons3);

  QVBoxLayout* rightLayout = new QVBoxLayout;
  rightLayout->addWidget(label);
  //rightLayout->addWidget(tabWidget);
  //rightLayout->addWidget(summaryTextEdit);
  rightLayout->addWidget(detailsTextEdit);
  rightLayout->addLayout(buttons);

  //QSplitter *splitter = new QSplitter(parent);
  //splitter->addWidget(leftLayout);
  //splitter->addWidget(rightLayout);

  QHBoxLayout* mainLayout = new QHBoxLayout;
  mainLayout->addLayout(leftLayout);
  mainLayout->addLayout(rightLayout);

  centralWidget->setLayout(mainLayout);
  setCentralWidget(centralWidget);

  // connect Signals and Slots
  QObject::connect(pushButtonToday, SIGNAL(clicked()), this, SLOT(goToToday()));
  QObject::connect(calendarWidget, SIGNAL(selectionChanged()), this, SLOT(actualizeEntry()));
  QObject::connect(calendarWidget, SIGNAL(currentPageChanged(int, int)), this, SLOT(calendarMonthAndYear(int, int)));
  QObject::connect(pushButtonClipboard, SIGNAL(clicked()), this, SLOT(entriesToClipboard()));
  QObject::connect(pushButtonSave, SIGNAL(clicked()), this, SLOT(saveEntry()));
  QObject::connect(pushButton01, SIGNAL(clicked()), this, SLOT(changeEntry01()));
  QObject::connect(pushButton02, SIGNAL(clicked()), this, SLOT(changeEntry02()));
  QObject::connect(pushButton03, SIGNAL(clicked()), this, SLOT(changeEntry03()));
  QObject::connect(pushButton04, SIGNAL(clicked()), this, SLOT(changeEntry04()));
  QObject::connect(pushButton05, SIGNAL(clicked()), this, SLOT(changeEntry05()));
  QObject::connect(pushButton06, SIGNAL(clicked()), this, SLOT(changeEntry06()));
  //QObject::connect(pushButton07, SIGNAL(clicked()), calendarWidget, SLOT(showPreviousYear()));
  //QObject::connect(pushButton08, SIGNAL(clicked()), calendarWidget, SLOT(showPreviousMonth()));
  //QObject::connect(pushButton09, SIGNAL(clicked()), calendarWidget, SLOT(showNextMonth()));
  //QObject::connect(pushButton10, SIGNAL(clicked()), calendarWidget, SLOT(showNextYear()));
  connect(actionSave, SIGNAL(triggered()), this, SLOT(saveEntry()));

  entryDate = QDate::currentDate();
  directory = "E:\\Verschiedenes\\Notizbuecher\\Tagebuch\\";

  loadEntry();

  label->setText(entryDate.toString(dateFormat)); //Qt::SystemLocaleLongDate));

  calendarMonthAndYear(calendarWidget->yearShown(), calendarWidget->monthShown());
  detailsTextEdit->setFont(QFont::QFont("Courier New", 10, 0, false));
}

Diary::~Diary()
{
  saveEntry();
}

void Diary::changeEntry01()
{
  calendarWidget->setSelectedDate(entryDate.addYears(-1));
}
void Diary::changeEntry02()
{
  calendarWidget->setSelectedDate(entryDate.addMonths(-1));
}
void Diary::changeEntry03()
{
  calendarWidget->setSelectedDate(entryDate.addDays(-1));
}
void Diary::changeEntry04()
{
  calendarWidget->setSelectedDate(entryDate.addDays(1));
}
void Diary::changeEntry05()
{
  calendarWidget->setSelectedDate(entryDate.addMonths(1));
}
void Diary::changeEntry06()
{
  calendarWidget->setSelectedDate(entryDate.addYears(1));
}

void Diary::entriesToClipboard()
{
  saveEntry(); // aktuellen Eintrag abspeichern - dann ist das restliche Handling einfacher

  QString stringClipboard = "";

  for (int i = anzahlTage->value() - 1; i > -1; i--)   // Bsp: anzahlTage.value() = 6 -> i = 5 ... 0
  {
    // Datum berechnen
    QDate date = entryDate.addDays(-i);

    QString srcFileName = directory;
    srcFileName.append(date.toString(Qt::ISODate));
    srcFileName.append(".txt");

    QFile srcFile(srcFileName);

    if (srcFile.open(QIODevice::ReadOnly))   // existiert das File?
    {
      if (stringClipboard.length() > 0)
      {
        // Zeilenumbrüche anhängen
        stringClipboard.append("\n\n\n");
      }

      QTextStream in(&srcFile);
      stringClipboard.append(date.toString(dateFormat));
      stringClipboard.append("\n");
      stringClipboard.append(in.readAll());
    }
  }

  // Zwischenablage füllen
  QClipboard* clipboard = QApplication::clipboard();
  clipboard->setText(stringClipboard, QClipboard::Clipboard);
}

void Diary::calendarMonthAndYear(int year, int month)
{
  QDate date(year, month, 1);
  QString string = date.toString("MMMM yyyy");
  calendarLabel->setText(string);
}

void Diary::goToToday()
{
  QDate today = QDate::currentDate();
  calendarWidget->setSelectedDate(today);
  label->setText(today.toString(dateFormat)); //Qt::SystemLocaleLongDate));
}

void Diary::actualizeEntry()
{
  saveEntry();
  entryDate = calendarWidget->selectedDate();
  detailsTextEdit->clear();
  loadEntry();
  label->setText(entryDate.toString(dateFormat)); //Qt::SystemLocaleLongDate));
}

void Diary::saveEntry()
{
  if (detailsTextEdit->toPlainText() == loadedEntry)
  {
    return;
  }

  QFile destFile(createFileString());

  if (destFile.open(QIODevice::WriteOnly))
  {
    QTextStream out(&destFile);
    out << detailsTextEdit->toPlainText();
    destFile.close();
  }
}

void Diary::loadEntry()
{
  QFile srcFile(createFileString());

  if (srcFile.open(QIODevice::ReadOnly))
  {
    QTextStream in(&srcFile);
    loadedEntry = in.readAll();
    detailsTextEdit->setText(loadedEntry);
  }
  else
  {
    loadedEntry = "";
  }
}

QString Diary::createFileString()
{
  //return QString(directory + QVariant(entryDate.year()).toString() + "/" + entryDate.toString(Qt::ISODate) + ".txt");
  return QString(directory + entryDate.toString(Qt::ISODate) + ".txt");
}
