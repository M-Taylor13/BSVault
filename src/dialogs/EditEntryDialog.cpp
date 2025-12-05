#include "EditEntryDialog.h"
#include "ui/dialogs/ui_EditEntryDialog.h"
#include "ui_EditEntryDialog.h"


EditEntryDialog::EditEntryDialog(VaultEntry* entry, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditEntryDialog)
    , m_entry(entry)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->eName->setText(m_entry->name);
    ui->eUser->setText(m_entry->username);
    ui->ePwd->setText(m_entry->password);
}

EditEntryDialog::~EditEntryDialog()
{
    delete ui;
}

void EditEntryDialog::on_eBtn_clicked() {
    QString eName = ui->eName->text();
    QString eUser = ui->eUser->text();
    QString ePwd = ui->ePwd->text();

    if (eName != "" && eUser != "" && ePwd != "") {
        m_entry->name = eName;
        m_entry->username = eUser;
        m_entry->password = ePwd;
        emit updateEntry(*m_entry);
        accept();
    }
    else {
        ui->eErrorLabel->setText("Error: All entries must be filled.");
    }
}

void EditEntryDialog::on_eCancelBtn_clicked() {
    reject();
}
