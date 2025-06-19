#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Reset();
    ShowQuestion();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Reset() {
    // Инициализация интервала.
}

void MainWindow::ShowQuestion() {
    // Показываем вопрос, используя ui->lbl_question->setText.
    // Если b_ - a_ <= 1, то мы угадали. Нужно показать не вопрос,
    // а ответ.
}

void MainWindow::on_btn_yes_clicked() {
    // Ответ "Да".
    // Делаем шаг алгоритма и обновляем вопрос.
}

void MainWindow::on_btn_no_clicked() {
    // Ответ "Нет".
    // Делаем шаг алгоритма и обновляем вопрос.
}
