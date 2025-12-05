#ifndef NEWLOGINDIALOG_H
#define NEWLOGINDIALOG_H

#include "Vault.h"
#include <QDialog>

namespace Ui {
class NewLoginDialog;
}

class NewLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewLoginDialog(Vault* vault, QWidget *parent = nullptr);
    ~NewLoginDialog();
    bool initCrypto();
    bool pwdValid();

private:
    Ui::NewLoginDialog *ui;
    Vault* m_vault;

private slots:
    void on_newBtn_clicked();
    void on_showBtn_clicked();
};

#endif // NEWLOGINDIALOG_H
