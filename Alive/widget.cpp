#include "widget.h"
#include "ui_widget.h"

#include <QNetworkRequest>
#include <QNetworkAccessManager>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    networkAccessManager = new QNetworkAccessManager(this);
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    networkAccessManager->get(QNetworkRequest(QUrl("http://assistenzplaner.de/PHP/alive.php?name=horst")));
}
