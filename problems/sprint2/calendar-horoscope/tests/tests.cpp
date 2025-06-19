#include <QtTest>

#include <QCoreApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QComboBox>

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

#include <mainwindow.h>
#include <magic_horoscope.h>

#include "test_utils/practicum_assert.hpp"


template<typename T>
void getChild(T*& child, QObject* parent, const QString& object_name, const QString& type_name)
{

    child = parent->findChild<T *>(object_name);
    QString message;
    if (type_name != "")
    {
        message = QString("В %3 не найден %1 типа %2").arg(object_name).arg(type_name).arg(parent->objectName());
    }
    else
    {
        message = QString("В %2 не найден %1").arg(object_name).arg(parent->objectName());;
    }

    QVERIFY2(child, qPrintable(message));
}

template<typename T>
T* getChild(QObject* parent, const QString& object_name, const QString& type_name = {})
{
    T* child = nullptr;
    getChild<T>(child, parent, object_name, type_name);

    return child;

}



class TestYourApp : public QObject
{
    Q_OBJECT

    template<class T>
    T* findElementByText(const QString& label) {
        for (T* button : window->findChildren<T*>())
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
    void init();
    void cleanup();
    void TestCalendar();
    void TestHoroscope();

    void TestDisabledData();

private:

    void checkCalendar();
    void checkHoroscope();
    void checkState();


    MainWindow* window;

    QLineEdit* le_year;

    QGroupBox* gb_calendar;
    QRadioButton* rb_eastern;
    QRadioButton* rb_tibetan;

    QRadioButton* rb_zoroastrian;

    QGroupBox* gb_horoscope;
    QRadioButton* rb_zodiac;

    QRadioButton* rb_druid;
    QCheckBox* cb_is_date;
    QSpinBox* sb_day;

    QComboBox* cb_month;

    QLabel* lbl_calendar;
    QLabel* lbl_horoscope;

};


void TestYourApp::initTestCase()
{

}

void TestYourApp::init()
{
    window = new MainWindow();
    QVERIFY2(window != nullptr, "Окно приложения не создано");
    window->show();
    QVERIFY2(window->isVisible(), "Окно приложения не активируется");

    gb_calendar = getChild<QGroupBox>(window, "gb_calendar", "QGroupBox");
    gb_horoscope = getChild<QGroupBox>(window, "gb_horoscope", "QGroupBox");

    rb_eastern = getChild<QRadioButton>(window, "rb_eastern", "QRadioButton");
    rb_tibetan = getChild<QRadioButton>(window, "rb_tibetan", "QRadioButton");
    rb_zoroastrian = getChild<QRadioButton>(window, "rb_zoroastrian", "QRadioButton");

    rb_zodiac = getChild<QRadioButton>(window, "rb_zodiac", "QRadioButton");
    rb_druid = getChild<QRadioButton>(window, "rb_druid", "QRadioButton");

    le_year = getChild<QLineEdit>(window, "le_year", "QLineEdit");

    cb_is_date = getChild<QCheckBox>(window, "cb_is_date", "QCheckBox");
    sb_day = getChild<QSpinBox>(window, "sb_day", "QSpinBox");
    cb_month = getChild<QComboBox>(window, "cb_month", "QComboBox");

    lbl_calendar = getChild<QLabel>(window, "lbl_calendar", "QLabel");
    lbl_horoscope = getChild<QLabel>(window, "lbl_horoscope", "QLabel");


}


void TestYourApp::checkCalendar()
{

    if (le_year->text().isEmpty())
    {
        PRAC_COMPARE2(lbl_calendar->text(), "Введите год",
                 "В случае, если год не задан, надпись lbl_calendar должна быть \"Введите год\"");
        return;
    }

    int year = le_year->text().toInt();
    if (rb_tibetan->isChecked() or rb_zoroastrian->isChecked())
    {

        QString animal = rb_tibetan->isChecked()
            ? GetAnimalForTibetanCalendar(year)
            : GetAnimalForZoroastrianCalendar(year);

        QString expected_calendar = QString("%1 — это год %2")
                                        .arg(le_year->text())
                                        .arg(animal);

        PRAC_COMPARE2(lbl_calendar->text(), expected_calendar,
                 "Вывод символа года не совпадает с ожидаемым для тибетского / зороастрийского календаря");

    }
    else
    {
        QString animal = GetAnimalForEasternCalendar(year);
        QString element = GetElementForEasternCalendar(year);

        QString expected_calendar = QString("%1 — это год %2. Стихия/цвет — %3")
                                        .arg(le_year->text())
                                        .arg(animal)
                                        .arg(element);
        PRAC_COMPARE2(lbl_calendar->text(), expected_calendar,
                 "Вывод символа года не совпадает с ожидаемым для восточного календаря");
    }
}

void TestYourApp::checkHoroscope()
{

    if (!cb_is_date->isChecked())
    {
        PRAC_COMPARE2(lbl_horoscope->text(), "Ввод даты отключён",
                 "При выключенном вводе даты надпись lbl_horoscope должна быть \"Ввод даты отключён\"");
        return;
    }

    int day = sb_day->value();
    int month = cb_month->currentIndex() + 1;
    int year = le_year->text().toInt();

    if (rb_zodiac->isChecked())
    {

        QString expected_symbol = GetZodiac(day, month, year);

        QString expected_horoscope =
            QString("%1.%2 — ваш знак зодиака %3 по зодиакальному гороскопу")
                .arg(day, 2, 10, QChar('0')).arg(month, 2, 10, QChar('0')).arg(expected_symbol);


        PRAC_COMPARE2(lbl_horoscope->text(), expected_horoscope,
                "Выведенный гороскоп не соответствует ожидаемому для зодиакального гороскопа");
    }
    else
    {
        QString expected_tree = GetTree(day, month, year);

        QString expected_horoscope =
            QString("%1.%2 — ваше тотемное дерево %3 по гороскопу друидов")
                .arg(day, 2, 10, QChar('0')).arg(month, 2, 10, QChar('0')).arg(expected_tree);

        PRAC_COMPARE2(lbl_horoscope->text(), expected_horoscope,
                 "Выведенный гороскоп не соответствует ожидаемому для гороскопа друидов");
    }
}

void TestYourApp::checkState()
{
    checkCalendar();
    checkHoroscope();
}

void mouseClick(QWidget* where_to_click)
{
    QTest::mouseClick(where_to_click, Qt::LeftButton);
}

void TestYourApp::TestDisabledData()
{
    cb_is_date->setChecked(false);
    checkHoroscope();
}

void TestYourApp::TestCalendar()
{
    le_year->setText("2000");
    mouseClick(rb_eastern);
    checkCalendar();

    le_year->setText("2024");
    mouseClick(rb_tibetan);
    checkCalendar();

    le_year->setText("1986");
    mouseClick(rb_zoroastrian);
    checkCalendar();
}

void TestYourApp::TestHoroscope()
{
    cb_is_date->setChecked(true);

    auto setDate = [this] (int day, int month, int year)
    {
        sb_day->setValue(day);
        cb_month->setCurrentIndex(month - 1);
        le_year->setText(QString("%1").arg(year));
    };

    auto checkDate = [this, setDate] (int day, int month, int year)
    {
        setDate(day, month, year);
        checkHoroscope();
    };

    auto checkNonExistingDate = [this, setDate] (int day, int month, int year)
    {
        setDate(day, month, year);

        PRAC_COMPARE2(lbl_horoscope->text(), "Такой даты не существует", "При вводе несуществующей даты надпись lbl_horoscope должна быть \"Такой даты не существует\"");

    };

    rb_zodiac->setChecked(true);
    checkDate(12, 6, 1986);
    checkDate(15, 3, 2015);
    checkDate(3, 12, 2076);

    rb_druid->setChecked(true);
    PRAC_COMPARE(rb_zodiac->isChecked(), false);
    PRAC_COMPARE(rb_druid->isChecked(), true);

    checkDate(9, 3, 2006);
    checkDate(8, 12, 2007);
    checkDate(25, 02, 1976);


    rb_zodiac->setChecked(true);

    checkNonExistingDate(29, 2, 2001);
    checkNonExistingDate(31, 6, 2012);

    rb_druid->setChecked(true);
    checkNonExistingDate(30, 2, 2020);
    checkNonExistingDate(31, 9, 2035);
}

void TestYourApp::cleanupTestCase()
{
}

void TestYourApp::cleanup()
{
    delete window;
}

QTEST_MAIN(TestYourApp)

#include "tests.moc"
