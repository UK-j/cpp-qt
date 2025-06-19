#pragma once


inline void clickWidget(QWidget* widget)
{
    QTest::mouseClick(widget, Qt::LeftButton);
}
