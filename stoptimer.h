#ifndef STOPTIMER_H
#define STOPTIMER_H

#include <QObject>
#include <QTimer>


class Stoptimer
{
public:
    Stoptimer();

    QTimer* GetTimer();
    unsigned long GetTimerValue();
    void StartTimer();
    void StopTimer();
    void ResetTimer();

protected:
    QTimer* timer = nullptr;

    unsigned long totalMs;
    int baseTimerOffset = 10;
};

#endif // STOPTIMER_H
