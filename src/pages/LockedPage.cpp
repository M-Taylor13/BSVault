#include "LockedPage.h"
#include "ui_LockedPage.h"

LockedPage::LockedPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LockedPage)
{
    ui->setupUi(this);
}

LockedPage::~LockedPage()
{
    delete ui;
}
