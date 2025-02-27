#include "stoptimer.h"

Stoptimer::Stoptimer()
{
    timer = new QTimer();
    totalMs = 0;
}

QTimer* Stoptimer::GetTimer()
{
    return timer;
}

unsigned long Stoptimer::GetTimerValue()
{
    if (timer->isActive())
    {
        totalMs += baseTimerOffset;
    }

    return totalMs;
}


void Stoptimer::StartTimer()
{
    timer->start(baseTimerOffset);
}

void Stoptimer::StopTimer()
{
    timer->stop();
}

void Stoptimer::ResetTimer()
{
    timer->stop();
    totalMs = 0;
}
