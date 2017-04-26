#include <QSettings>
#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SearchableTextEdit.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->search->setVisible(false);

  m_settings = new QSettings("Ulle", "SearchAndMarkText", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  ui->checkBoxCaseSensitive->setChecked(m_settings->value("caseSensitive").toBool());

  ui->textEdit1->setText(m_settings->value("text1").toString());
  ui->textEdit2->setText(m_settings->value("text2").toString());

  ui->lineEditSearch->setText(m_settings->value("search").toString());

  m_textEdits.append(ui->textEdit1);
  m_textEdits.append(ui->textEdit2);

}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("search", ui->lineEditSearch->text());
  m_settings->setValue("caseSensitive", ui->checkBoxCaseSensitive->isChecked());
  m_settings->setValue("text1", ui->textEdit1->text());
  m_settings->setValue("text2", ui->textEdit2->text());

  delete ui;
}

void MainWindow::on_lineEditSearch_textChanged(const QString &searchString)
{
  doSearch();

}

void MainWindow::on_actionFind_triggered()
{

  ui->search->setVisible(true);
  ui->lineEditSearch->setFocus();

  for (auto it : m_textEdits)
  {
    it->setResultsVisible(true);
  }

  doSearch();
}

void MainWindow::on_checkBoxCaseSensitive_stateChanged(int arg1)
{
  doSearch();
}

void MainWindow::doSearch()
{
  for (auto it : m_textEdits)
  {
    it->doSearch(ui->lineEditSearch->text(), ui->checkBoxCaseSensitive->isChecked());
  }
}

void MainWindow::resetSearch()
{
  for (auto it : m_textEdits)
  {
    it->resetSearch();
  }
}

void MainWindow::on_pushButtonClose_clicked()
{
    ui->search->setVisible(false);
    resetSearch();
}
