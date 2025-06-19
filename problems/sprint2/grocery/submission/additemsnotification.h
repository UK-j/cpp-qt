#ifndef ADDITEMSNOTIFICATION_H
#define ADDITEMSNOTIFICATION_H

#include <QDialog>

namespace Ui {
class AddItemsNotification;
}

class AddItemsNotification : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemsNotification(QWidget *parent = nullptr);
    ~AddItemsNotification();

private:
    Ui::AddItemsNotification *ui;
};

#endif // ADDITEMSNOTIFICATION_H
