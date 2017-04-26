#include <QCoreApplication>
#include <windows.h>

#include <iostream>

int main(int argc, char *argv[])
{
    LARGE_INTEGER processStart;
    QueryPerformanceCounter(&processStart);

    std::cout << "processStart.QuadPart" << processStart.QuadPart << std::endl;

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

    const int sleepTimeInMilliseconds = 1000;

    while (true)
    {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);

        double timeInMilliSeconds = double(now.QuadPart - processStart.QuadPart) / frequency.QuadPart * 1000.0;

        std::cout << "Elapsed time in milliseconds since process start: " << timeInMilliSeconds << std::endl;

        Sleep(sleepTimeInMilliseconds);
    }
}
