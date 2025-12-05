#ifndef VAULTLISTPAGE_H
#define VAULTLISTPAGE_H

#include <QWidget>
#include "Vault.h"
#include "VaultListModel.h"

namespace Ui {
class VaultListPage;
}

class VaultListPage : public QWidget
{
    Q_OBJECT

public:
    explicit VaultListPage(Vault* vault, QWidget *parent = nullptr);
    ~VaultListPage();

private:
    Ui::VaultListPage *ui;
    VaultListModel *m_model;
    Vault *m_vault;

private slots:
    void on_addBtn_clicked();
    void on_editBtn_clicked();
    void on_deleteBtn_clicked();
};

#endif // VAULTLISTPAGE_H
