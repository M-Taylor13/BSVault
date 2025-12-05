#include "ConfirmDeleteDialog.h"
#include "ui_ConfirmDeleteDialog.h"

ConfirmDeleteDialog::ConfirmDeleteDialog(int rowNum, Vault* vault, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmDeleteDialog)
    , m_vault(vault)
    , m_row(rowNum)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    VaultEntry entry = m_vault->entries()[m_row];
    ui->delConfirmLabel->setText(QString("Confirm deletion of login details for %1?").arg(entry.name));
}

ConfirmDeleteDialog::~ConfirmDeleteDialog()
{
    delete ui;
}

void ConfirmDeleteDialog::on_deleteCancelBtn_clicked() {
    reject();
}

void ConfirmDeleteDialog::on_deleteBtn_clicked() {
    m_vault->deleteEntry(m_row);
    emit itemDeleted(m_row);
    accept();
}
