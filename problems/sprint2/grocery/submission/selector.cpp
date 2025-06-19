#include "selector.h"
#include "ui_selector.h"
#include <QLabel>
#include "cartwindow.h"
#include "additemsnotification.h"
#include "cartwindow.h"

bool IsValueInVector(const std::vector<QString>& vector, QString value) {
    for (const auto& item: vector) {
        if (item == value) {
            return true;
        }
    }

    return false;
}

Selector::Selector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Selector)
{
    ui->setupUi(this);
    items = std::vector<ShopItem>({
        {ui->lbl_item_1, ui->lbl_cost_1, ui->lbl_q_1},
        {ui->lbl_item_2, ui->lbl_cost_2, ui->lbl_q_2},
        {ui->lbl_item_3, ui->lbl_cost_3, ui->lbl_q_3},
        {ui->lbl_item_4, ui->lbl_cost_4, ui->lbl_q_4},
        {ui->lbl_item_5, ui->lbl_cost_5, ui->lbl_q_5},
        {ui->lbl_item_6, ui->lbl_cost_6, ui->lbl_q_6},
        {ui->lbl_item_7, ui->lbl_cost_7, ui->lbl_q_7},
        {ui->lbl_item_8, ui->lbl_cost_8, ui->lbl_q_8},
        {ui->lbl_item_9, ui->lbl_cost_9, ui->lbl_q_9},
        {ui->lbl_item_10, ui->lbl_cost_10, ui->lbl_q_10},
        {ui->lbl_item_11, ui->lbl_cost_11, ui->lbl_q_11},
        {ui->lbl_item_12, ui->lbl_cost_12, ui->lbl_q_12},
        {ui->lbl_item_13, ui->lbl_cost_13, ui->lbl_q_13},
        {ui->lbl_item_14, ui->lbl_cost_14, ui->lbl_q_14},
        {ui->lbl_item_15, ui->lbl_cost_15, ui->lbl_q_15}
    });

    for(const auto& item : items) {
        item.item_name->SetCountLabel(item.item_count);
    }
}

Selector::~Selector()
{
    delete ui;
}

void Selector::on_btn_cart_clicked()
{
    // Напишите этот метод.
}

std::vector<CartItem> Selector::GetCartItems() const {
    std::vector<CartItem> result;
    for(const auto& v : items) {
        int count = v.item_name->GetSelectedCount();

        if (count == 0) {
            continue;
        }

        result.push_back({
            v.item_name->text(),
            v.item_price->text().toDouble(),
            count
        });
    }

    return result;
}

void Selector::AddAll(const std::vector<QString> &items_to_add)
{
    for (const auto& item : items) {
        if (IsValueInVector(items_to_add, item.item_name->text())) {
            item.item_name->Inc();
        }
    }
}

void Selector::on_btn_clear_clicked()
{
    for (const auto& v : items) {
        v.item_name->SetSelectedCount(0);
    }
}

void Selector::on_pb_fruit_clicked()
{
    static const std::vector<QString> items_to_add{
        "Яблоки",
        "Персики",
        "Манго",
        "Бананы",
        "Мандарины"};

    AddAll(items_to_add);
}

void Selector::on_pb_vegetable_clicked()
{
    static const std::vector<QString> items_to_add{
       "Картофель",
       "Морковь",
       "Лук",
       "Баклажаны",
       "Редис",
       "Огурцы"};

    AddAll(items_to_add);
}

void Selector::on_pb_drink_clicked()
{

    static const std::vector<QString> items_to_add{
        "Чай",
        "Кофе",
        "Вода",
        "Молоко"
    };

    AddAll(items_to_add);
}
