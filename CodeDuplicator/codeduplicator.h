#ifndef REPLACEPRO_H
#define REPLACEPRO_H

#include <QtGui/QWidget>
class QCheckBox;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QString;
class QTextEdit;

class CodeDuplicator : public QWidget
{
  Q_OBJECT

public:
  CodeDuplicator(QWidget* parent = 0);
  ~CodeDuplicator();

private:
  QCheckBox* checkBoxLeadingZeros;
  QLineEdit* lineEditEingabe;
  QPushButton* pushButtonCopyResultToClipboard;
  QSpinBox* spinBoxNumberOfEmptyLines;
  QSpinBox* spinBoxLow;
  QSpinBox* spinBoxHigh;
  QSpinBox* spinBoxStepSize;
  QString* stringConfigurationFile;
  QTextEdit* textEditTemplate;
  QTextEdit* textEditResult;

public slots:
  QString createNumberStringWithLeadingZeros(int, int);
  void createResult();
  void copyResultToClipboard();
  void readConfigurationFile();
  void setDefaults();
  void writeConfigurationFile();
};

#endif // REPLACEPRO_H
