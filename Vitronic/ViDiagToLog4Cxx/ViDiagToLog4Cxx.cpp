#include "ViDiagToLog4Cxx.h"
#include "ui_ViDiagToLog4Cxx.h"

#include <QMessageBox>
#include <QClipboard>

ViDiagToLog4Cxx::ViDiagToLog4Cxx(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ViDiagToLog4Cxx)
{
  ui->setupUi(this);

  connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
}

ViDiagToLog4Cxx::~ViDiagToLog4Cxx()
{
  delete ui;
}

void ViDiagToLog4Cxx::clipboardDataChanged()
{
  if (!ui->checkBoxAutoConvert->isChecked())
  {
    return;
  }

  QString converted = convertViDiagToLog4Cxx(QApplication::clipboard()->text());
  if (!converted.isEmpty())
  {
    disconnect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
    QApplication::clipboard()->setText(converted);
    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));
  }
}

void ViDiagToLog4Cxx::on_lineEditViDiag_editingFinished()
{
  ui->lineEditLog4Cxx->clear();

  QString log4CxxString = convertViDiagToLog4Cxx(ui->lineEditViDiag->text());

  if (!log4CxxString.isEmpty())
  {
    ui->lineEditLog4Cxx->setText(log4CxxString);
  }
}

QString ViDiagToLog4Cxx::convertViDiagToLog4Cxx(const QString &viDiag)
{
  QString log4CxxString;

  // ViDIAGX (1, "%d. ViIO-Geraet '%s' gefunden\n", i, szTestDeviceName);
  // 1st Parameter -> Testlevel -> 0 = FATAL, 1 = ERRROR, ...

  // ViDIAG0 (testlevel, string)
  // ViDIAG1 (testlevel, string, value1)
  // ViDIAG2 (testlevel, string, value1, value2)
  // ...
  // ViDIAG8 (testlevel, string, value1, value2, ..., value8)

  // --> LOG4CXX_WARN(logger, __FUNCTION__ << i << ". ViIO-Geraet '" << szTestDeviceName << "' gefunden");

  QString simplified = viDiag.simplified();

  int indexOfPlaceholderString = 0;
  int parameterIndex = 0;
  int offset = 0;
  if (simplified.left(6) == "ViDIAG" )
  {
    offset = 2;
    parameterIndex = 2;
    indexOfPlaceholderString = 1;
  }
  else if (simplified.left(4) == "Diag")
  {
    offset = 3;
    parameterIndex = 3;
    indexOfPlaceholderString = 2;
  }
  else
  {
    return log4CxxString;
  }

  int leftParanthesis = simplified.indexOf("(");
  int rightParanthesis = simplified.lastIndexOf(")");

  if (leftParanthesis < 0 || rightParanthesis <  0)
  {
    return log4CxxString;
  }

  QStringList parameters = simplified.mid(leftParanthesis + 1, rightParanthesis - leftParanthesis - 1).split(",");

  if (parameters.count() < offset)
  {
    if (simplified.left(11) == "ViDIAG_INFO" && parameters.count() == 1)
    {
      log4CxxString = QString("LOG4CXX_INFO(%1, __FUNCTION__ << \" \" << %2);").arg(ui->lineEditLogger->text()).arg(parameters[0]);
    }
    return log4CxxString;
  }

  if (parameters[indexOfPlaceholderString].count("%") != parameters.length() - offset)
  {
    return log4CxxString;
  }

  for (auto it = parameters.begin(); it != parameters.end(); it++)
  {
    *it = (*it).simplified();
  }

  bool conversionSuccessfull;
  int logLevel = parameters[0].toInt(&conversionSuccessfull);
  if (conversionSuccessfull)
  {
    switch(logLevel)
    {
    case 0:
      log4CxxString = "LOG4CXX_FATAL";
      break;
    case 1:
      log4CxxString = "LOG4CXX_ERROR";
      break;
    case 2:
      log4CxxString = "LOG4CXX_WARN";
      break;
    case 3:
      log4CxxString = "LOG4CXX_INFO";
      break;
    case 4:
      log4CxxString = "LOG4CXX_DEBUG";
      break;
    default:
      log4CxxString = "LOG4CXX_TRACE";
    }
  }
  else
  {
    if (parameters[0] == "DIAG_ERROR")
    {
      log4CxxString = "LOG4CXX_ERROR";
    }
    else if (parameters[0] == "DIAG_WARNING")
    {
      log4CxxString = "LOG4CXX_WARN";
    }
    else if (parameters[0] == "DIAG_INFO")
    {
      log4CxxString = "LOG4CXX_INFO";
    }
    else if (parameters[0] == "DIAG_TRACE")
    {
      log4CxxString = "LOG4CXX_DEBUG";
    }
    else if (parameters[0] == "DIAG_FINE_DETAIL")
    {
      log4CxxString = "LOG4CXX_TRACE";
    }
    else
    {
      log4CxxString = "LOG4CXX_TRACE";
    }
  }

  while(parameters[indexOfPlaceholderString].contains("%"))
  {
    // todo endless loop, when string with %-sign is replaced?
    parameters[indexOfPlaceholderString].replace(parameters[indexOfPlaceholderString].indexOf("%"), 2, QString("\" << %1 << \"").arg(parameters[parameterIndex++]));
  }

  if (simplified.left(6) == "ViDIAG" )
  {
    log4CxxString.append(QString("(%1, __FUNCTION__ << \" \" << %2);").arg(ui->lineEditLogger->text()).arg(parameters[indexOfPlaceholderString]));
  }
  else
  {
    log4CxxString.append(QString("(%1, __FUNCTION__ << \" Acq-Channel: \" << %2 << \" \" << %3);").arg(ui->lineEditLogger->text()).arg(parameters[1]).arg(parameters[indexOfPlaceholderString]));
  }
  

  return log4CxxString;
}
