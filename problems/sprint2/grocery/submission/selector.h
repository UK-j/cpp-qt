#pragma once

#include <QMainWindow>
#include <vector>
#include <QLabel>

#include "definitions.h"
#include "clickablelabel.h"

namespace Ui {
class Selector;
}

struct ShopItem {
    ClickableLabel* item_name;
    QLabel* item_price;
    QLabel* item_count;
};

class Selector : public QMainWindow
{
    Q_OBJECT

public:
    explicit Selector(QWidget *parent = nullptr);
    ~Selector();

private slots:
    void on_btn_cart_clicked();

    void on_btn_clear_clicked();

    void on_pb_fruit_clicked();

    void on_pb_vegetable_clicked();

    void on_pb_drink_clicked();

private:
    std::vector<CartItem> GetCartItems() const;
    void AddAll(const std::vector<QString>& items);

private:
    Ui::Selector *ui;
    std::vector<ShopItem> items;
};
