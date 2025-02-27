#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <thread>
#include <sstream>

#include "stoptimer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class TimerState
{
    Started,
    Stopped
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_startStop_clicked();
    void on_pb_clear_released();
    void on_pb_lap_clicked();
    void UpdateTimer();

private:
    Ui::MainWindow *ui;

    TimerState timerState;
    Stoptimer* stoptimer = nullptr;

    size_t lapCounter;
    unsigned long lapTime;

    QString defaultTimerValue ="0:0:0";

    void InitUi();
    void Routine();
    QString ConvertToQStr(const unsigned long& ms);

};

#endif // MAINWINDOW_H
