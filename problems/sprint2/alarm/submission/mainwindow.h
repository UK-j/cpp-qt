#pragma once

#include <QMainWindow>
#include <prac/QTimer>
#include <prac/QMediaPlayer>
#include <prac/QTime>
#include <prac/QDateTime>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QDateTime GetAlarmMoment() const {
        return alarm_moment_;
    }

private slots:
    // Тут объявите слоты.

private:
    Ui::MainWindow *ui;
    QDateTime alarm_moment_;
};
