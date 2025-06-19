
#include "utils.h"



void check_items_layout(Selector* window, const std::map<void*, QHBoxLayout*>& horizontal_map,
                        const std::map<void*, QGridLayout*>& grid_map) {
    auto check_item_layout = [&](QLabel* label_ptr, const QString& label_name) {
        auto horizontal_pair = horizontal_map.find(static_cast<void*>(label_ptr));
        QVERIFY2(horizontal_pair != horizontal_map.end(),
                 qPrintable(QString("Элемент %1 должен находиться в горизонтальной компоновке")
                                .arg(label_name)));

        auto horizontal_layout = horizontal_pair->second;
        auto grid_layout = grid_map.find(static_cast<void*>(horizontal_layout));
        QVERIFY2(grid_layout != grid_map.end(),
                 qPrintable(QString("Горизонтальный компоновщик элемента %1 должен находиться в "
                                    "компоновке по сетке")
                                .arg(label_name)));
    };

    for (int i = 1; i <= 15; ++i) {
        QString item = QString("lbl_item_%1").arg(i);
        QString cost = QString("lbl_cost_%1").arg(i);
        QString quantity = QString("lbl_q_%1").arg(i);

        auto lbl_item = FindElementByName<QLabel>(window, item);
        auto lbl_cost = FindElementByName<QLabel>(window, cost);
        auto lbl_quantity = FindElementByName<QLabel>(window, quantity);

        QVERIFY2(lbl_item, qPrintable(QString("Элемент %1 не найден").arg(item)));
        QVERIFY2(lbl_cost, qPrintable(QString("Элемент %1 не найден").arg(cost)));
        QVERIFY2(lbl_quantity, qPrintable(QString("Элемент %1 не найден").arg(quantity)));

        check_item_layout(lbl_item, item);
        check_item_layout(lbl_cost, cost);
        check_item_layout(lbl_quantity, quantity);
    }
}

void check_grid_layout(Selector* window, const std::map<void*, QVBoxLayout*>& vertical_map,
                       const std::map<void*, QHBoxLayout*>& horizontal_map) {
    auto grid_layout_list = window->findChildren<QGridLayout*>();
    QVERIFY2(grid_layout_list.size() == 1, "На форме должен быть ровно один компоновщик по сетке");

    auto grid_layout = grid_layout_list.first();

    auto horizontal_pair = horizontal_map.find(static_cast<void*>(grid_layout));
    QVERIFY2(
        horizontal_pair != horizontal_map.end(),
        qPrintable(QString("Компоновщик по сетке должен находиться в горизонтальной компоновке")));

    auto horizontal_layout = horizontal_pair->second;
    auto vertical_layout = vertical_map.find(static_cast<void*>(horizontal_layout));
    QVERIFY2(vertical_layout != vertical_map.end(),
             qPrintable(QString("Горизонтальный компоновщик компоновщика по сетке должен "
                                "находиться в вертикальном компоновщике")));
}

void check_add_pbs(Selector* window, const std::map<void*, QVBoxLayout*>& vertical_map,
                   const std::map<void*, QHBoxLayout*>& horizontal_map) {
    auto check_single_pb = [&](const QString& item) {
        auto pb = FindElementByName<QPushButton>(window, item);
        QVERIFY2(pb, qPrintable(QString("Кнопка %1 не найдена на форме").arg(item)));

        auto vertical_pair = vertical_map.find(static_cast<void*>(pb));
        QVERIFY2(vertical_pair != vertical_map.end(),
                 qPrintable(
                     QString("Кнопка %1 должна находиться в вертикальном компоновщике").arg(item)));

        auto vertical_layout = vertical_pair->second;

        auto horizontal_pair = horizontal_map.find(static_cast<void*>(vertical_layout));
        QVERIFY2(horizontal_pair != horizontal_map.end(),
                 qPrintable(QString("Вертикальный копоновщик кнопки %1 должен находиться в "
                                    "горизонтальном компоновщике")
                                .arg(item)));

        auto horizontal_layout = horizontal_pair->second;

        auto vertical_pair_2 = vertical_map.find(static_cast<void*>(horizontal_layout));
        QVERIFY2(vertical_pair_2 != vertical_map.end(),
                 qPrintable(QString("Горизонтальный копоновщик кнопки %1 должен находиться в "
                                    "вертикальном компоновщике")
                                .arg(item)));
    };

    check_single_pb("pb_fruit");
    check_single_pb("pb_vegetable");
    check_single_pb("pb_drink");
}

void check_cart_buttons(Selector* window, const std::map<void*, QVBoxLayout*>& vertical_map,
                        const std::map<void*, QHBoxLayout*>& horizontal_map) {
    auto check_single_btn = [&](const QString& item) {
        auto btn = FindElementByName<QPushButton>(window, item);
        QVERIFY2(btn, qPrintable(QString("Кнопка %1 не найдена на форме").arg(item)));

        auto horizontal_pair = horizontal_map.find(static_cast<void*>(btn));
        QVERIFY2(
            horizontal_pair != horizontal_map.end(),
            qPrintable(
                QString("Кнопка %1 должна находиться в горизонтальном компоновщике").arg(item)));

        auto horizontal_layout = horizontal_pair->second;

        auto vertical_pair = vertical_map.find(static_cast<void*>(horizontal_layout));
        QVERIFY2(vertical_pair != vertical_map.end(),
                 qPrintable(QString("Горизонтальный компоновщик кнопки %1 должен находиться в "
                                    "вертикальном компоновщике")
                                .arg(item)));
    };

    check_single_btn("btn_cart");
    check_single_btn("btn_clear");
}
