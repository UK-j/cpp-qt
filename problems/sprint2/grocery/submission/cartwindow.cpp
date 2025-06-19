#include "cartwindow.h"
#include "ui_cartwindow.h"

CartWindow::CartWindow(const std::vector<CartItem>& items, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CartWindow)
{
    ui->setupUi(this);

    double sum = 0;

    for (const auto& item : items) {
        double price = item.item_price * item.item_count;
        ui->listWidget->addItem(item.item_name + " × " + QString::number(item.item_count) + " - " + QString::number(price));
        sum += price;
    }

    ui->label->setText("Итого: " + QString::number(sum));
}

CartWindow::~CartWindow()
{
    delete ui;
}
