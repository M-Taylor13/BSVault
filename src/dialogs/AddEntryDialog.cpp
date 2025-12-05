#include "AddEntryDialog.h"
#include "ui_AddEntryDialog.h"

AddEntryDialog::AddEntryDialog(Vault* vault, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEntryDialog)
    , m_vault(vault)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

AddEntryDialog::~AddEntryDialog()
{
    delete ui;
}

void AddEntryDialog::on_addCancelBtn_clicked() {
    reject();
}

void AddEntryDialog::on_addBtn_clicked() {
    QString name = ui->nameInput->text();
    QString username = ui->usernameInput->text();
    QString pwd = ui->pwdInput->text();
    bool success = m_vault->addEntry(name, username, pwd);
    if (success) {
        emit entryAdded(m_vault->entries().last());
        accept();
    } else {
        ui->aErrorLabel->setText("Error: All entries must be filled.");
    }
}



