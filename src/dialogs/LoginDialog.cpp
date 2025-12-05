#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QPasswordDigestor>
#include <QCryptographicHash>

LoginDialog::LoginDialog(Vault* vault, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
    , m_vault(vault)
{
    ui->setupUi(this);
    ui->pwdInput->setEchoMode(QLineEdit::Password);
    m_attempts = 3;
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


QByteArray LoginDialog::getKey() {
    QByteArray pwdTxt = ui->pwdInput->text().toUtf8();

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    QFile masterFile(path + "/master.hash");
    if (!masterFile.open(QIODevice::ReadOnly)) return nullptr;
    QByteArray salt = masterFile.read(16);
    masterFile.close();

    QByteArray derived =  QPasswordDigestor::deriveKeyPbkdf2(QCryptographicHash::Sha256,
                                                            pwdTxt, salt, 310000, 32);
    return derived;
}

void LoginDialog::on_showBtn_clicked() {
    if (ui->pwdInput->echoMode() == QLineEdit::Password) {
        ui->pwdInput->setEchoMode(QLineEdit::Normal);
        ui->showBtn->setText("hide");
    } else {
        ui->pwdInput->setEchoMode(QLineEdit::Password);
        ui->showBtn->setText("show");
    }
}


void LoginDialog::on_unlockBtn_clicked() {
    m_attempts -= 1;
    QByteArray key = getKey();
    if (key.size() == 32) {
        m_vault->setKey(key);
        bool result = m_vault->loadEncrypted();
        if (result) {
            emit loginSuccess();
            accept();
        } else {
            if (m_attempts < 1) {
                reject();
            }
            else if (m_attempts < 2) {
                ui->errorLabel->setText("Incorrect password. 1 attempt remains.");
            } else {
                ui->errorLabel->setText("Incorrect password");
            }

            ui->pwdInput->setText("");
        }

    } else {
        ui->errorLabel->setText("Error logging in");
    }

}


