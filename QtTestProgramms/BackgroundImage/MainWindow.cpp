#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->mainToolBar->setStyleSheet("background-repeat: no-repeat; background-position: right top; background-image: url(:/images/CompanyLogo.bmp); border: 0px");
  ui->mainToolBar->setMinimumHeight(40);

  m_mdiAreaBackground = new MdiAreaBackground(":/images/CompanyLogo.bmp", this);
  ui->verticalLayout->addWidget(m_mdiAreaBackground);
}

MainWindow::~MainWindow()
{
  delete ui;
}
