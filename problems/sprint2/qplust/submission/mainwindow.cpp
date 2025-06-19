#include "mainwindow.h"

#include "ui_mainwindow.h"

#include "sum.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btn_eq_clicked()
{
    bool ok;
    int q = ui->le_q->text().toInt(&ok);
    if (!ok) {
        return;
    }
    int t = ui->le_t->text().toInt(&ok);
    if (!ok) {
        return;
    }
    ui->le_qt->setText(QString::number(Sum(q, t)));
}
