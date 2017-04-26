#include <QCoreApplication>
#include <QThreadPool>
#include <QMutex>

#include <iostream>

class HeatThread : public QRunnable
{
public:
    HeatThread(int threadId, QMutex* mutex)
    {
        this->threadId = threadId;
        this->mutex = mutex;
    }

    int threadId;
    QMutex* mutex;
    void run()
    {
        int i = 1;
        mutex->lock();
        std::cout << "starting thread: " << threadId << std::endl;
        mutex->unlock();
        while (true)
        {
            i *= 2;
            i += 2;
        }
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    std::cout << "start heating" << std::endl;
    QMutex* stdMutex = new QMutex();
    for (int i = 0; i < QThreadPool::globalInstance()->maxThreadCount() - 1; i++)
    {
        HeatThread* heatThread = new HeatThread(i, stdMutex);
        QThreadPool::globalInstance()->start(heatThread);
    }

    
    return a.exec();
}
