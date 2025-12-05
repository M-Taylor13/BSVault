#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "Vault.h"
#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(Vault *vault, QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    QByteArray getKey();
    Vault *m_vault;
    int m_attempts;

private slots:
    void on_unlockBtn_clicked();
    void on_showBtn_clicked();

signals:
    void loginSuccess();
};

#endif // LOGINDIALOG_H
