#include "mainwindow.h"
#include "NewLoginDialog.h"
#include "ui_mainwindow.h"
#include <QStackedWidget>
#include "LockedPage.h"
#include "VaultListPage.h"
#include <QFile>
#include <QStandardPaths>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stackedWidget = ui->mainStackedWidget;

    QWidget* lockedPage = new LockedPage(this);

    setWindowTitle("  BSVault");
    setWindowIcon(QIcon(":/images/BSlogo.png"));

    stackedWidget->addWidget(lockedPage);
    stackedWidget->setCurrentWidget(lockedPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startLoginFlow() {

    m_vault = Vault();


    if (!LoginExists()) {
        NewLoginDialog* newLogin = new NewLoginDialog(&m_vault, this);
        int result = newLogin->exec();
        newLogin->deleteLater();
        if (result != QDialog::Accepted) {
            QCoreApplication::quit();
            return;
        }
    }

    loginWindow = new LoginDialog(&m_vault, this);

    connect(loginWindow, &LoginDialog::loginSuccess, this, [this]() {
        QWidget* listPage = new VaultListPage(&m_vault, this);
        stackedWidget->addWidget(listPage);
        stackedWidget->setCurrentWidget(listPage);
    });
    int result = loginWindow->exec();
    loginWindow->deleteLater();
    if (result != QDialog::Accepted) {
        QCoreApplication::quit();
        return;
    }
}

bool MainWindow::LoginExists() {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QFileInfo masterFile(path + "/master.hash");
    return masterFile.exists() && masterFile.isFile() && masterFile.size() > 0;
}


void MainWindow::closeEvent(QCloseEvent *event) {
    m_vault.encrypt();
    event->accept();
}
