#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QSettings>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_lastDisplayedHandId(0)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "PokerAssistant", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  updateInformation();

  if (m_settings->contains("currentHandId"))
  {
    ui->lineEditHandId->setText(m_settings->value("currentHandId").toString());
  }

  m_timer = new QTimer(this);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(updateInformation()));
  m_timer->start(1000);
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("currentHandId", ui->lineEditHandId->text());
  delete ui;
}

void MainWindow::updateInformation()
{
  m_handHistory.parseFolder();

  if (m_lastDisplayedHandId != m_handHistory.lastHandId())
  {
    m_lastDisplayedHandId = m_handHistory.lastHandId();
    ui->plainTextEditGeneralInformation->setPlainText(m_handHistory.information());
  }
}

void MainWindow::on_lineEditHandId_textChanged(const QString &arg1)
{
  ui->plainTextEditHandInformation->setPlainText(m_handHistory.handInformation(arg1.toULongLong()));
}
