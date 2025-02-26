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

    InitUi();

    connect(ui->pb_clear, &QPushButton::released, this, &MainWindow::on_pb_clear_released);

    std::thread thread1 = std::thread(&MainWindow::Routine, this);
    thread1.detach();
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
    }
    else if (timerState == TimerState::Started)
    {
        ui->pb_startStop->setText(QString("Start"));
        timerState = TimerState::Stopped;
        stoptimer->StopTimer();
    }
}


void MainWindow::on_pb_clear_released()
{
    if (timerState == TimerState::Started) {
        on_pb_startStop_clicked();
    }

    lapCounter = 0;
    ui->l_timeLabel->setText(defaultTimerValue);
    ui->tb_timingField->clear();
}


void MainWindow::on_pb_lap_clicked()
{
    std::stringstream result;
    result << "Lap: "
           << ++lapCounter
           << " Time: "
           << ui->l_timeLabel->text().toStdString();
    ui->tb_timingField->append(QtPrivate::convertToQString(result.str()));
}

void MainWindow::Routine()
{
    while (true)
    {
        while (timerState == TimerState::Started)
        {
            ui->l_timeLabel->setText(QString(stoptimer->GetTimerValue()));
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


void MainWindow::InitUi()
{
    ui->gb_info->setTitle(QString("Info"));
    ui->gb_control->setTitle(QString("Control"));

    ui->l_timeLabel->setText(defaultTimerValue);

    ui->pb_startStop->setText(QString("Start"));
    ui->pb_clear->setText(QString("Clear"));
    ui->pb_lap->setText(QString("Lap"));

}


