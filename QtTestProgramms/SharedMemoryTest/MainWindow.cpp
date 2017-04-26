#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QSharedMemory>
#include <QMessageBox>
#include <QDebug>
#include <QList>
#include <QDataStream>
#include <QBuffer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Test: Wieviel Bilder könnte man anlegen?
    int i = 0;
    while(true)
    {
        QSharedMemory* leak = new QSharedMemory(QString("%1").arg(i));
        bool sucess = leak->create(1024 * 1024 * 100);
        if (!sucess)
        {
            break;
        }
        i++;
        qDebug() << i;
    }


    // Test: kann man dynamische Strukturen verwenden?
    QStringList test;
    test.append("Hello");
    test.append("world!\n");
    test.append("How");
    test.append("are");
    test.append("you");
    test.append("doing?");
    // -> man muss die dynamischen Strukturen selber serialisieren (QDataStream  ?)

    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    qDebug() << "buffer size before writing: " << buffer.size();
    QDataStream dataStream(&buffer);
    dataStream << test;
    qDebug() << "buffer size after writing: " << buffer.size();


    QStringList testIn;
    dataStream >> testIn;
    qDebug() << "length of testIn" << testIn.length();
    for (int i = 0; i < testIn.length(); i++)
    {
        qDebug() << i << ": " << testIn.at(i);
    }

    /*QVariant test2 (test);
    //test2.toByteArray();
    qDebug() << test2.type();
    qDebug() << test2.canConvert(QVariant::ByteArray);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
