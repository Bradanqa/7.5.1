#include "stoptimer.h"

Stoptimer::Stoptimer()
{
    timer = new QTimer();
}

QString Stoptimer::GetTimerValue()
{
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
    auto total_sec = std::chrono::duration_cast<std::chrono::seconds>(elapsedTime).count();

    int min = total_sec / 60;
    int sec = total_sec % 60;
    int milli = elapsedTime.count() % 1000;

    return QString("Time %1:%2:%3")
            .arg(min)
            .arg(sec)
            .arg(milli);
}


void Stoptimer::StartTimer()
{
    timer->start();
    startTime = std::chrono::steady_clock::now();
}

void Stoptimer::StopTimer()
{
    timer->stop();
}

