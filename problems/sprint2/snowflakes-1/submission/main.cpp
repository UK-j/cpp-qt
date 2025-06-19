#include "winterwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WinterWindow w;
    w.show();
    return a.exec();
}
