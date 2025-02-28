#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timerState = TimerState::Stopped;
    stoptimer = new Stoptimer;
    lapCounter = 0;
    lapTime = 0;

    InitUi();

    connect(stoptimer->GetTimer(), &QTimer::timeout, this, &MainWindow::UpdateTimer);
    connect(ui->pb_clear, &QPushButton::released, this, &MainWindow::on_pb_clear_released);
}

MainWindow::~MainWindow()
{
    delete stoptimer;
    delete ui;
}

void MainWindow::on_pb_startStop_clicked()
{
    if (timerState == TimerState::Stopped)
    {
        ui->pb_startStop->setText(QString("Stop"));
        timerState = TimerState::Started;
        stoptimer->StartTimer();
        ui->pb_lap->setEnabled(true);
    }
    else if (timerState == TimerState::Started)
    {
        ui->pb_startStop->setText(QString("Start"));
        timerState = TimerState::Stopped;
        stoptimer->StopTimer();
        ui->pb_lap->setEnabled(false);
    }
}


void MainWindow::on_pb_clear_released()
{
    lapCounter = 0;
    lapTime = 0;

    ui->l_timeLabel->setText(defaultTimerValue);
    ui->tb_timingField->clear();

    stoptimer->ResetTimer();
}


void MainWindow::on_pb_lap_clicked()
{
    if (stoptimer->GetTimerValue() == 0) {
        return;
    }

    std::stringstream result;
    result << "Lap: "
           << ++lapCounter
           << " Time: ";

    ui->tb_timingField->append(
                QtPrivate::convertToQString(result.str())
                + ConvertToQStr(stoptimer->GetTimerValue() - lapTime));

    lapTime = stoptimer->GetTimerValue();
}

void MainWindow::UpdateTimer()
{
    ui->l_timeLabel->setText(ConvertToQStr(stoptimer->GetTimerValue()));
}


void MainWindow::InitUi()
{
    ui->gb_info->setTitle(QString("Info"));
    ui->gb_control->setTitle(QString("Control"));

    ui->l_timeLabel->setText(defaultTimerValue);

    ui->pb_startStop->setText(QString("Start"));
    ui->pb_clear->setText(QString("Clear"));
    ui->pb_lap->setText(QString("Lap"));
    ui->pb_lap->setEnabled(false);

}

QString MainWindow::ConvertToQStr(const uint32_t& ms)
{
    unsigned long min = (ms % 3600000) / 60000;
    unsigned long sec = (ms % 60000) / 1000;
    unsigned long milli = ms % 1000;

    return QString("Time %1:%2:%3").arg(min).arg(sec).arg(milli);
}

