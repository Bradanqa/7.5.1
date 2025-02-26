#ifndef STOPTIMER_H
#define STOPTIMER_H

#include <QObject>
#include <QTimer>


class Stoptimer
{
public:
    Stoptimer();

    QString GetTimerValue();
    void StartTimer();
    void StopTimer();

protected:
    QTimer* timer = nullptr;
    std::chrono::milliseconds totalMs;
    std::chrono::steady_clock::time_point startTime;
};

#endif // STOPTIMER_H
