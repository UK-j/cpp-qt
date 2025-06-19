#pragma once

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyWindowWithImage;
}
QT_END_NAMESPACE

// В этот класс добавьте метод FitToImage.
class MyWindowWithImage : public QMainWindow
{
    Q_OBJECT

public:
    MyWindowWithImage(QWidget *parent = nullptr);
    ~MyWindowWithImage();

    void SetPixmap(QLabel* label_pix, const QString path);

    void FitToImage(QLabel* label);

private:
    Ui::MyWindowWithImage *ui;
};
