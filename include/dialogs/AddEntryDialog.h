#ifndef ADDENTRYDIALOG_H
#define ADDENTRYDIALOG_H

#include <QDialog>
#include "Vault.h"

namespace Ui {
class AddEntryDialog;
}

class AddEntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEntryDialog(Vault* vault, QWidget *parent = nullptr);
    ~AddEntryDialog();

signals:
    void entryAdded(const VaultEntry& entry);

private:
    Ui::AddEntryDialog *ui;
    Vault *m_vault;

private slots:
    void on_addBtn_clicked();
    void on_addCancelBtn_clicked();
};

#endif // ADDENTRYDIALOG_H
