#ifndef STOPTIMER_H
#define STOPTIMER_H

#include <QObject>
#include <QTimer>


class Stoptimer
{
public:
    Stoptimer();

    QTimer* GetTimer();
    uint32_t GetTimerValue();
    void StartTimer();
    void StopTimer();
    void ResetTimer();

protected:
    QTimer* timer = nullptr;

    uint32_t totalMs;
    uint32_t baseTimerOffset = 10;
};

#endif // STOPTIMER_H
