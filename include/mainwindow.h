#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qstackedwidget.h>
#include "Vault.h"
#include "LoginDialog.h"
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startLoginFlow();
    bool LoginExists();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QStackedWidget* stackedWidget;
    LoginDialog *loginWindow = nullptr;
    Vault m_vault;
};
#endif // MAINWINDOW_H
