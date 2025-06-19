#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rb_asc_clicked()
{
    // Ваш код.
}

void MainWindow::on_rb_desc_clicked()
{
    // Ваш код.
}

void MainWindow::on_cb_case_clicked()
{
    // Ваш код.
}

void MainWindow::on_le_unsorted_textChanged(const QString&)
{
    // Ваш код.
}
