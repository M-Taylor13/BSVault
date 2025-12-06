#include "NewLoginDialog.h"
#include "ui_NewLoginDialog.h"
#include <QPasswordDigestor>
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <qregularexpression.h>


NewLoginDialog::NewLoginDialog(Vault* vault, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewLoginDialog)
    , m_vault(vault)
{
    ui->setupUi(this);
    ui->newPwdInput->setEchoMode(QLineEdit::Password);
    ui->newErrorMsg->setWordWrap(true);
    ui->newErrorMsg->setSizePolicy(
        QSizePolicy::Preferred,    // horizontal: use preferred width
        QSizePolicy::MinimumExpanding // vertical: expand if needed
        );

}

NewLoginDialog::~NewLoginDialog()
{
    delete ui;
}

bool NewLoginDialog::pwdValid() {
    QString pwd = ui->newPwdInput->text();
    QRegularExpression regex("^(?=.*[A-Z])(?=.*[a-z])(?=.*[0-9])(?=.*[@$!%*?&])[A-Za-z0-9@$!%*?&]{8,}$");
    QRegularExpressionMatch result = regex.match(pwd);
    if (result.hasMatch()) {
        return true;
    }
    return false;
}


void NewLoginDialog::on_newBtn_clicked() {
    if (!pwdValid()) {
        ui->newErrorMsg->setText("Passwords must contain an uppercase and lowercase letter, a number, no whitespace, and be 8 or more characters in length.");
    } else {
        if (initCrypto()) {
            accept();
        } else {
            ui->newErrorMsg->setText("Password was unable to be set, try again.");
        }
    }

}

void NewLoginDialog::on_showBtn_clicked() {
    if (ui->newPwdInput->echoMode() == QLineEdit::Password) {
        ui->newPwdInput->setEchoMode(QLineEdit::Normal);
        ui->showBtn->setText("hide");
    } else {
        ui->newPwdInput->setEchoMode(QLineEdit::Password);
        ui->showBtn->setText("show");
    }
}

bool NewLoginDialog::initCrypto() {
    QByteArray pwd = ui->newPwdInput->text().toUtf8();
    QByteArray salt(16, 0);
    QRandomGenerator *generator = QRandomGenerator::system();
    for (int i = 0; i < salt.size(); i++) {
       salt[i] = static_cast<char>(generator->bounded(0, 256));
    }

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    QFile masterFile(path + "/master.hash");
    if (!masterFile.open(QIODevice::WriteOnly)) return false;
    masterFile.write(salt);
    masterFile.close();

    QByteArray derived =  QPasswordDigestor::deriveKeyPbkdf2(QCryptographicHash::Sha256,
                                                            pwd, salt, 310000, 32);
    m_vault->setKey(derived);
    m_vault->encrypt();
    return true;
}
