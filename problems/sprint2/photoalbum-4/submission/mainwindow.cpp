#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаем QLabel для изображения
    lbl_img = new QLabel(this);
    lbl_img->setAlignment(Qt::AlignCenter);

    // Настройка кнопок
    ui->btn_left->setIcon(QIcon(":/icons/chevron_l.png"));
    ui->btn_right->setIcon(QIcon(":/icons/chevron_r.png"));
    ui->btn_left->setIconSize(QSize(32, 32));
    ui->btn_right->setIconSize(QSize(32, 32));
    ui->btn_left->setStyleSheet("border: none; background: transparent;");
    ui->btn_right->setStyleSheet("border: none; background: transparent;");

    // Установка папки с изображениями
    SetFolder(":/cats/images/");
}

MainWindow::~MainWindow()
{
    delete lbl_img;
    delete ui;
}

void MainWindow::SetFolder(const QString& dir)
{
    current_folder = dir;
    QDir qdir(dir);
    QStringList files = qdir.entryList({"*.jpg", "*.png"}, QDir::Files, QDir::Name);

    // Сбрасываем индекс при смене папки
    cur_file_index = files.isEmpty() ? -1 : 0;

    // Обновляем изображение и состояние кнопок
    SetPixmap(GetCurrentFile());
    UpdateEnabled();
}

QString MainWindow::GetCurrentFile()
{
    QDir dir(current_folder);
    QStringList files = dir.entryList({"*.jpg", "*.png"}, QDir::Files, QDir::Name);

    if (files.isEmpty() || cur_file_index < 0 || cur_file_index >= files.size()) {
        return QString();
    }

    return dir.filePath(files[cur_file_index]);
}

void MainWindow::SetPixmap(const QString& path)
{
    if (path.isEmpty()) {
        lbl_img->clear();
        return;
    }

    if (active_pixmap.load(path)) {
        lbl_img->setPixmap(active_pixmap);
        FitImage();
    }
}

QPixmap MainWindow::ResizeImgToFit(const QPixmap &src, int window_width, int window_height)
{
    int img_w = src.width();
    int img_h = src.height();

    double w_ratio = double(img_w) / window_width;
    double h_ratio = double(img_h) / window_height;

    if (w_ratio < h_ratio) {
        return src.scaledToWidth(window_width);
    } else {
        return src.scaledToHeight(window_height);
    }
}

void MainWindow::FitImage()
{
    if (active_pixmap.isNull()) return;

    int win_w = width();
    int win_h = height();

    QPixmap scaled = ResizeImgToFit(active_pixmap, win_w, win_h);
    lbl_img->setPixmap(scaled);
    lbl_img->resize(scaled.size());
    lbl_img->move((win_w - scaled.width()) / 2, (win_h - scaled.height()) / 2);
}

void MainWindow::UpdateEnabled()
{
    QDir dir(current_folder);
    QStringList files = dir.entryList({"*.jpg", "*.png"}, QDir::Files, QDir::Name);

    bool hasFiles = !files.isEmpty();
    bool isFirst = cur_file_index <= 0;
    bool isLast = cur_file_index >= files.size() - 1;

    ui->btn_left->setEnabled(hasFiles && !isFirst);
    ui->btn_right->setEnabled(hasFiles && !isLast);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    FitImage();
}

void MainWindow::on_btn_left_clicked()
{
    QDir dir(current_folder);
    QStringList files = dir.entryList({"*.jpg", "*.png"}, QDir::Files, QDir::Name);

    if (!files.isEmpty() && cur_file_index > 0) {
        cur_file_index--;
        SetPixmap(GetCurrentFile());
        UpdateEnabled();
    }
}


void MainWindow::on_btn_right_clicked()
{
    QDir dir(current_folder);
    QStringList files = dir.entryList({"*.jpg", "*.png"}, QDir::Files, QDir::Name);

    if (!files.isEmpty() && cur_file_index < files.size() - 1) {
        cur_file_index++;
        SetPixmap(GetCurrentFile());
        UpdateEnabled();
    }
}

