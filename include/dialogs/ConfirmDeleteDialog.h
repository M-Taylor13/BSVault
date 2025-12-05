#ifndef CONFIRMDELETEDIALOG_H
#define CONFIRMDELETEDIALOG_H

#include <QDialog>
#include "VaultEntry.h"
#include "Vault.h"

namespace Ui {
class ConfirmDeleteDialog;
}

class ConfirmDeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmDeleteDialog(int rowNum, Vault* vault, QWidget *parent = nullptr);
    ~ConfirmDeleteDialog();

signals:
    void itemDeleted(int row);

private:
    Ui::ConfirmDeleteDialog *ui;
    Vault* m_vault;
    int m_row;

private slots:
    void on_deleteBtn_clicked();
    void on_deleteCancelBtn_clicked();
};

#endif // CONFIRMDELETEDIALOG_H
