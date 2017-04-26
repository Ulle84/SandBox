#include "codeduplicator.h"
#include <QtGui>
#include <iostream>

// ToDos
// Umstellung auf UI File
// Abstandshalter nach SpinBox 'leere Zwischenzeilen' einfügen
// setDefaults Funktion schreiben
// wie kann man den CheckBoxState speichern und wieder laden
// Basis-Klasse Window
// auf Model/View Ansatz umstellen
// Schriftart abhängig vom Betriebssystem

// Enhancements
// Programmicon hinzufügen
// abhänig von der Nummer Code erzeugen oder nicht (##1## -> nur wenn # = 1, dann Code erzeugen)

// Ideen
// 28.06.2012 Eingabe der Parameter per Text: replace # by starting with: 2 ending at: 5 stepsize: 1
// Funktionen createWidgets, initWidgets, createLayout, connectSignalsAndSlots (Nachteil: alle Widgets müssen als Klassenelement vorhanden sein)
// Checkbox: Ergebnisse sofort generieren Ja/Nein (auto-update) (wenn Nein, dann Button sichtbar schalten)
// Werte aus Konfigurations-Datei ein- und auslesen
// Anzahl der Ersetzungen in Statusleiste rausgeben
// Blockweise / Zeilenweise Ersetzung
// 2. Tab: strings ersetzen
// Liste mit Ersetzungen 1. "=" -> " = "; 2. "  =" -> " ="; 3.
// PrettyPrintIdee PrettyPrint aufsetzend auf Liste mit Ersetzungen -> reguläre Ausdrücke
// "  " -> " "
// "=" -> " = "
// "  =" -> " ="
// "=  " -> "= "
// "+" -> " + "
// "  +" -> " +"
// "+  " -> "+ "
// "+ =" -> "+="

CodeDuplicator::CodeDuplicator(QWidget* parent) : QWidget(parent)
{

  // create widgets
  checkBoxLeadingZeros = new QCheckBox(tr("führende Nullen voranstellen"));
  lineEditEingabe = new QLineEdit();
  pushButtonCopyResultToClipboard = new QPushButton(tr("Kopiere Ergebnis in Zwischenablage"));
  spinBoxNumberOfEmptyLines = new QSpinBox();
  spinBoxLow = new QSpinBox();
  spinBoxHigh = new QSpinBox();
  spinBoxStepSize = new QSpinBox();
  textEditTemplate = new QTextEdit();
  textEditResult = new QTextEdit();

  // init widgets
  spinBoxLow->setMaximum(1000);
  spinBoxHigh->setMaximum(1000);
  spinBoxStepSize->setMinimum(1);
  textEditResult->setReadOnly(true);
  textEditTemplate->setFont(QFont::QFont("Courier", 10, 0, false));
  textEditResult->setFont(QFont::QFont("Courier", 10, 0, false));

  stringConfigurationFile = new QString("configuration.dat");
  readConfigurationFile();

  // create layouts
  QHBoxLayout* hBoxLayout01 = new QHBoxLayout();
  QHBoxLayout* hBoxLayout02 = new QHBoxLayout();
  QVBoxLayout* vBoxLayout01 = new QVBoxLayout();

  // compose widgets
  hBoxLayout01->addWidget(new QLabel(tr("Ersetze")));
  hBoxLayout01->addWidget(lineEditEingabe);
  hBoxLayout01->addWidget(new QLabel(tr("durch")));
  hBoxLayout01->addWidget(spinBoxLow);
  hBoxLayout01->addWidget(new QLabel(tr("bis")));
  hBoxLayout01->addWidget(spinBoxHigh);
  hBoxLayout01->addWidget(new QLabel(tr("Schrittweite")));
  hBoxLayout01->addWidget(spinBoxStepSize);
  hBoxLayout01->addWidget(pushButtonCopyResultToClipboard);

  hBoxLayout02->addWidget(new QLabel(tr("Anzahl der leeren Zwischenzeilen:")));
  hBoxLayout02->addWidget(spinBoxNumberOfEmptyLines);

  vBoxLayout01->addWidget(new QLabel(tr("Vorlage")));
  vBoxLayout01->addWidget(textEditTemplate);
  vBoxLayout01->addWidget(new QLabel(tr("Ergebnis")));
  vBoxLayout01->addWidget(textEditResult);
  vBoxLayout01->addLayout(hBoxLayout01);
  vBoxLayout01->addLayout(hBoxLayout02);
  vBoxLayout01->addWidget(checkBoxLeadingZeros);

  setLayout(vBoxLayout01);

  // connect signals and slots
  connect(checkBoxLeadingZeros, SIGNAL(stateChanged(int)), this, SLOT(createResult()));
  connect(lineEditEingabe, SIGNAL(textChanged(QString)), this, SLOT(createResult()));
  connect(pushButtonCopyResultToClipboard, SIGNAL(clicked()), this, SLOT(copyResultToClipboard()));
  connect(spinBoxHigh, SIGNAL(valueChanged(int)), this, SLOT(createResult()));
  connect(spinBoxLow, SIGNAL(valueChanged(int)), this, SLOT(createResult()));
  connect(spinBoxStepSize, SIGNAL(valueChanged(int)), this, SLOT(createResult()));
  connect(spinBoxNumberOfEmptyLines, SIGNAL(valueChanged(int)), this, SLOT(createResult()));
  connect(textEditTemplate, SIGNAL(textChanged()), this, SLOT(createResult()));
}

CodeDuplicator::~CodeDuplicator()
{
  writeConfigurationFile();
}

void CodeDuplicator::createResult()
{
  textEditResult->clear();
  QString newText = "";

  if (textEditTemplate->toPlainText().contains(lineEditEingabe->text(), Qt::CaseSensitive))
  {
    if (lineEditEingabe->text().length() > 0 && textEditTemplate->toPlainText().length() >= lineEditEingabe->text().length())
    {
      for (int i = spinBoxLow->value(); i <= spinBoxHigh->value(); i += spinBoxStepSize->value())
      {
        QString string = textEditTemplate->toPlainText();

        if (checkBoxLeadingZeros->isChecked())
        {
          string.replace(lineEditEingabe->text(), createNumberStringWithLeadingZeros(i, spinBoxHigh->value()));
        }
        else
        {
          QVariant number(i);
          string.replace(lineEditEingabe->text(), number.toString());
        }

        newText.append(string + "\n");

        if (i < spinBoxHigh->value())
        {
          for (int j = 0; j < spinBoxNumberOfEmptyLines->value(); j++)
          {
            newText.append("");
          }
        }
      }
    }
  }

  textEditResult->setPlainText(newText);
}

void CodeDuplicator::copyResultToClipboard()
{
  QApplication::clipboard()->setText(textEditResult->toPlainText());
}

QString CodeDuplicator::createNumberStringWithLeadingZeros(int num, int maxNum)
{
  QString result = "";
  int numOfLeadingZeros = QVariant(maxNum).toString().length() - QVariant(num).toString().length();

  for (int i = 0; i < numOfLeadingZeros; i++)
  {
    result.append("0");
  }

  result.append(QVariant(num).toString());
  return result;
}



void CodeDuplicator::writeConfigurationFile()
{
  //QString directory = QDir::homePath();
  QFile file(*stringConfigurationFile);

  if (!file.open(QIODevice::WriteOnly))
  {
    std::cerr << "Cannot open file for writing: " << qPrintable(file.errorString()) << std::endl;
    return;
  }

  QDataStream out(&file);
  out.setVersion(QDataStream::Qt_4_8);

  out << lineEditEingabe->text();
  out << spinBoxHigh->value();
  out << spinBoxLow->value();
  out << spinBoxNumberOfEmptyLines->value();
  out << spinBoxStepSize->value();
  out << checkBoxLeadingZeros->isChecked();
  out << textEditTemplate->toPlainText();
}

void CodeDuplicator::readConfigurationFile()
{
  QFile file(*stringConfigurationFile);

  if (!file.open(QIODevice::ReadOnly))
  {
    std::cerr << "Cannot open file for reading: " << qPrintable(file.errorString()) << std::endl;
    setDefaults();
    return;
  }

  QDataStream in(&file);
  in.setVersion(QDataStream::Qt_4_8);

  QString stringInput;
  int intInput;
  bool boolInput;

  in >> stringInput;
  lineEditEingabe->setText(stringInput);

  in >> intInput;
  spinBoxHigh->setValue(intInput);

  in >> intInput;
  spinBoxLow->setValue(intInput);

  in >> intInput;
  spinBoxNumberOfEmptyLines->setValue(intInput);

  in >> intInput;
  spinBoxStepSize->setValue(intInput);

  in >> boolInput;
  checkBoxLeadingZeros->setChecked(boolInput);

  in >> stringInput;
  textEditTemplate->setPlainText(stringInput);
}

void CodeDuplicator::setDefaults()
{
  lineEditEingabe->setText("#");
  spinBoxHigh->setValue(4);
  spinBoxLow->setValue(1);
  spinBoxNumberOfEmptyLines->setValue(1);
}
