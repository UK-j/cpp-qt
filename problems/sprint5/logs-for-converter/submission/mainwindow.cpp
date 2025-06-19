#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

double MainWindow::ConvertToMiles(double km) {
    return km * coef;
}

double MainWindow::ConvertToKm(double miles) {
    return miles / coef;
}

void MainWindow::on_btn_convert_to_miles_clicked() {
    bool ok;
    auto input_text = ui->txt_km_input->text();
    double km = input_text.toDouble(&ok);

    if (ok) {
        double miles = ConvertToMiles(km);
        ui->result_label_miles->setText("  = " + QString::number(miles) + " miles");
    } else {
        ui->result_label_miles->setText("Invalid input for km");
    }
}

void MainWindow::on_btn_convert_to_km_clicked() {
    bool ok;
    auto input_text = ui->txt_miles_input->text();
    double miles = input_text.toDouble(&ok);

    if (ok) {
        double km = ConvertToKm(miles);
        ui->result_label_km->setText("  = " + QString::number(km) + " km");
    } else {
        ui->result_label_km->setText("Invalid input for miles");
    }
}
