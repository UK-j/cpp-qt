#include "additemsnotification.h"
#include "ui_additemsnotification.h"

AddItemsNotification::AddItemsNotification(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddItemsNotification)
{
    ui->setupUi(this);
}

AddItemsNotification::~AddItemsNotification()
{
    delete ui;
}
