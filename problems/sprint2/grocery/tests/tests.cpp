
// Core headers
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLabel>

#include <QtTest>

#include "selector.h"
#include "additemsnotification.h"
#include "cartwindow.h"

#include "utils.h"

class TestYourApp : public QObject
{
    Q_OBJECT

    template<class T>
    T* findElementByText(const QString& label) {
        for (T* button : selector_window->findChildren<T*>())
        {
            if (button->text() == label)
            {
                return button;
            }
        }
        return nullptr;
    }

public:
    TestYourApp()=default;
    ~TestYourApp()=default;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void TestSelectorLayout();
    void TestAddItemsNotificationLayout();
    void TestCartWindowLayout();



private:
    Selector* selector_window;
    QPushButton* btn_cart;

};


void TestYourApp::initTestCase()
{


    selector_window = new Selector();
    QVERIFY2(selector_window != nullptr, "Окно приложения не создано");
    selector_window->show();
    QVERIFY2(selector_window->isVisible(), "Окно приложения не активируется");

}

void TestYourApp::TestSelectorLayout()
{

    std::map<void*, QVBoxLayout*> vertical_map = get_layout_map<QVBoxLayout>(selector_window);
    auto horizontal_map = get_layout_map<QHBoxLayout>(selector_window);
    auto grid_map = get_layout_map<QGridLayout>(selector_window);

    check_items_layout(selector_window, horizontal_map, grid_map);
    check_grid_layout(selector_window, vertical_map, horizontal_map);
    check_add_pbs(selector_window, vertical_map, horizontal_map);
    check_cart_buttons(selector_window, vertical_map, horizontal_map);

}


void TestYourApp::TestAddItemsNotificationLayout(){

    auto ain = new AddItemsNotification();
    auto vertical_map = get_layout_map<QVBoxLayout>(ain);


    auto label = FindElementByName<QLabel>(ain, "label");
    QVERIFY2(label, qPrintable(QString("Надпись label не найдена на форме AddItemsNotification")));
    auto btn = FindElementByName<QPushButton>(ain, "pushButton");

    QVERIFY2(btn, qPrintable(QString("Кнопка pushButton не найдена на форме AddItemsNotification")));

    auto vertical_pair_label = vertical_map.find(static_cast<void *>(label));
    QVERIFY2(vertical_pair_label != vertical_map.end(),
             qPrintable(QString("Надпись label в окне AddItemsNotification должна находиться в вертикальном компоновщике")));

    auto vertical_pair_button = vertical_map.find(static_cast<void *>(label));
    QVERIFY2(vertical_pair_button != vertical_map.end(),
             qPrintable(QString("Кнопка pushButton в окне AddItemsNotification должна находиться в вертикальном компоновщике")));

    delete ain;
}



void TestYourApp::TestCartWindowLayout()
{
    std::vector<CartItem> items;
    auto cart_window = new CartWindow(items);
    auto vertical_map = get_layout_map<QVBoxLayout>(cart_window);

    auto list_widget = FindElementByName<QListWidget>(cart_window, "listWidget");
    QVERIFY2(list_widget, qPrintable(QString("Список listWidget не найден на форме CartWindow")));
    auto label = FindElementByName<QLabel>(cart_window, "label");
    QVERIFY2(label, qPrintable(QString("Надпись label не найдена на форме CartWindow")));
    auto btn = FindElementByName<QPushButton>(cart_window, "btn_close");
    QVERIFY2(btn, qPrintable(QString("Кнопка btn_close не найдена на форме CartWindow")));


    auto vertical_pair_list_widget = vertical_map.find(static_cast<void *>(list_widget));
    QVERIFY2(vertical_pair_list_widget != vertical_map.end(),
             qPrintable(QString("Список list_widget в окне CartWindow должна находиться в вертикальном компоновщике")));

    auto vertical_pair_label = vertical_map.find(static_cast<void *>(label));
    QVERIFY2(vertical_pair_label != vertical_map.end(),
             qPrintable(QString("Надпись label в окне CartWindow должна находиться в вертикальном компоновщике")));

    auto vertical_pair_button = vertical_map.find(static_cast<void *>(label));
    QVERIFY2(vertical_pair_button != vertical_map.end(),
             qPrintable(QString("Кнопка btn_close в окне CartWindow должна находиться в вертикальном компоновщике")));

    delete cart_window;
}


void TestYourApp::cleanupTestCase()
{
    delete selector_window;
}

QTEST_MAIN(TestYourApp)

#include "tests.moc"
