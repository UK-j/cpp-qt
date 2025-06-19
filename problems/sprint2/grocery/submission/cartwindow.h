#ifndef CARTWINDOW_H
#define CARTWINDOW_H

#include <QDialog>
#include "definitions.h"

namespace Ui {
class CartWindow;
}

class CartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CartWindow(const std::vector<CartItem>& items, QWidget *parent = nullptr);
    ~CartWindow();

private:
    Ui::CartWindow *ui;
};

#endif // CARTWINDOW_H
