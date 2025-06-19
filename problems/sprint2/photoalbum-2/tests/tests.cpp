#include <QtTest>
#include <QCoreApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

#include <mainwindow.h>

namespace {

template<class Widget>
Widget* FindElementByName(QMainWindow* window, const QString& name) {
    auto elements = window->findChildren<Widget*>();

    auto iter = std::find_if(elements.begin(), elements.end(), [&](Widget* elem){
        return elem->objectName() == name;
    });

    return iter == elements.end() ? nullptr : *iter;
}

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
    void TestDefault();
    void TestResize1();
    void TestResize2();
    void TestWidth1();
    void TestWidth2();
    void TestHeight1();
    void TestHeight2();
    void TestExtremeRatio1();
    void TestExtremeRatio2();

private:
    MainWindow* window;
    QLabel* lbl_img;
    QPixmap* pixmap;
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
    lbl_img = FindElementByName<QLabel>(window, "lbl_img");

    QVERIFY2(lbl_img, "Не найден элемент lbl_img класса QLabel");

    pixmap = new QPixmap(":/cats/images/cat1.jpg");
    QVERIFY2(!pixmap->isNull(), "Не удалось загрузить изображение");

}


inline int get_expected_coordinate(int window_side, int widget_side)
{
    int expected = (window_side - widget_side) / 2;
    return expected;
}

QPoint get_expected_pose(QWidget* window, QWidget* widget){

    auto x = get_expected_coordinate(window->width(), widget->width());
    auto y = get_expected_coordinate(window->height(), widget->height());

    return QPoint(x, y);
}

bool check_tolerance(int expected, int actual, double a_tol = 0, double r_tol = 0.05)
{

    auto diff = std::abs(actual - expected);
    bool in_tol;
    if (a_tol == 0)
    {
        in_tol = double(diff) < double(expected) * r_tol;
    }
    else
    {
        in_tol = double(diff) < a_tol;
    }

    return in_tol;
}


void check_widget_alignment(QWidget* parent, QWidget* child, double r_tol = 0.05)
{
    auto widget_pos = child->pos();
    auto widget_expected = get_expected_pose(parent, child);
    auto a_tol = parent->size() * r_tol;

    auto x_in_tol = check_tolerance(widget_expected.x(), widget_pos.x(), a_tol.width());
    auto y_in_tol = check_tolerance(widget_expected.y(), widget_pos.y(), a_tol.height());

    QVERIFY2(x_in_tol, "Координата X виджета lbl_img не соответствует ожидаемой.");
    QVERIFY2(y_in_tol, "Координата Y виджета lbl_img не соответствует ожидаемой.");
}

void check_lbl_alignment(QMainWindow* window, QLabel* widget, QPixmap* pixmap)
{

    int window_width = window->width();
    int window_height = window->height();

    int img_w = pixmap->width();
    int img_h = pixmap->height();

    double w_ratio = double(img_w) / double(window_width);
    double h_ratio = double(img_h) / double(window_height);
    double img_ratio = double(img_h) / double(img_w);

    QSize expected_size;

    if ( w_ratio <= h_ratio ) {
        // Scaled to width
        int width = window_width;
        int height = double(width) * img_ratio;
        expected_size = QSize(width, height);
    } else {
        // Scaled to height
        int height = window_height;
        int width = double(height) / img_ratio;
        expected_size = QSize(width, height);
    }

    QVERIFY2(check_tolerance(expected_size.width(), widget->width()), "Ширина lbl_img не совпадает с ожидаемой.");
    QVERIFY2(check_tolerance(expected_size.height(), widget->height()), "Высота lbl_img не совпадает с ожидаемой.");

    check_widget_alignment(window, widget);
}

void TestYourApp::TestDefault()
{
    check_lbl_alignment(window, lbl_img, pixmap);
}


void TestYourApp::TestResize1()
{
    window->resize(window->size() * 0.57);
    check_lbl_alignment(window, lbl_img, pixmap);
}

void TestYourApp::TestResize2()
{
    window->resize(window->size() * 1.65);
    check_lbl_alignment(window, lbl_img, pixmap);
}


void TestYourApp::TestWidth1()
{
    window->resize(window->width() * 0.75, window->height());
    check_lbl_alignment(window, lbl_img, pixmap);
}

void TestYourApp::TestWidth2()
{
    window->resize(window->width() * 1.36, window->height());
    check_lbl_alignment(window, lbl_img, pixmap);
}

void TestYourApp::TestHeight1()
{
    window->resize(window->width(), window->height() * 0.75);
    check_lbl_alignment(window, lbl_img, pixmap);
}

void TestYourApp::TestHeight2()
{
    window->resize(window->width(), window->height() * 1.36);
    check_lbl_alignment(window, lbl_img, pixmap);
}


void TestYourApp::TestExtremeRatio1()
{
    window->resize(window->width() * 0.1, window->height() * 5);
    check_lbl_alignment(window, lbl_img, pixmap);
}

void TestYourApp::TestExtremeRatio2()
{
    window->resize(window->width() * 6, window->height() * 0.2);
    check_lbl_alignment(window, lbl_img, pixmap);
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
