#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <prac/QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Присоедините аудио и видеовыходы к плееру.

    connect(&player_, &prac::QMediaPlayer::positionChanged, this, &MainWindow::on_position_changed);
    connect(&player_, &prac::QMediaPlayer::mediaStatusChanged, this, &MainWindow::on_media_status_changed);
    connect(&player_, &prac::QMediaPlayer::playbackStateChanged, this, &MainWindow::on_playback_state_changed);

    audio_output_.setVolume(1.f);
}

void MainWindow::on_position_changed(qint64 position) {
    // Реализуйте обработку сигнала.
}

void MainWindow::on_media_status_changed(QMediaPlayer::MediaStatus) {
    // Реализуйте обработку сигнала.
}

void MainWindow::on_playback_state_changed(QMediaPlayer::PlaybackState new_state) {
    // Реализуйте обработку сигнала.
}

void MainWindow::on_btn_choose_clicked()
{
    // Реализуйте обработку сигнала.
}

void MainWindow::on_btn_pause_clicked()
{
    // Реализуйте обработку сигнала.
}

void MainWindow::on_sld_volume_valueChanged(int value)
{
    // Реализуйте обработку сигнала.
}

void MainWindow::on_sld_pos_valueChanged(int value)
{
    // Реализуйте обработку сигнала.
}

MainWindow::~MainWindow()
{
    delete ui;
}
