#include "VaultListPage.h"
#include "ui_VaultListPage.h"
#include <qboxlayout.h>
#include <QDialog>
#include "AddEntryDialog.h"
#include "EditEntryDialog.h"
#include "ConfirmDeleteDialog.h"
#include "ShowButtonDelegate.h"


VaultListPage::VaultListPage(Vault* vault, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::VaultListPage)
    , m_vault(vault)
{
    ui->setupUi(this);

    QWidget* scrollContent = new QWidget();
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setContentsMargins(0, 0, 0, 0);
    scrollLayout->setSpacing(0);

    scrollLayout->addWidget(ui->vaultTableView);

    ui->vaultScrollArea->setWidget(scrollContent);
    ui->vaultScrollArea->setWidgetResizable(true);
    ui->vaultTableView->setShowGrid(false);
    ui->vaultTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->vaultTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->vaultTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->vaultTableView->horizontalHeader()->setVisible(false);
    ui->vaultTableView->verticalHeader()->setVisible(false);
    ui->vaultTableView->setStyleSheet(
        "QTableView {"
        "    border: none;"
        "    outline: none;"
        "}"
        "QTableView::item {"
        "    border: none;"
        "    padding: 6px;"
        "}"
        "QTableView::item:selected {"
        "    color: black;"
        "    background: #2596be;"
        "}"
        );
    ui->vaultScrollArea->setFrameShape(QFrame::NoFrame);
    ui->vaultTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    m_model = new VaultListModel(this);

    m_model->setEntries(m_vault->entries());

    ui->vaultTableView->setModel(m_model);

    ShowButtonDelegate* btnDelegate = new ShowButtonDelegate(this);

    ui->vaultTableView->setItemDelegateForColumn(3, btnDelegate);

    connect(btnDelegate, &ShowButtonDelegate::showBtnClicked, this, [=](QModelIndex index) {
        int row = index.row();
        VaultEntry entry = m_model->findEntry(row);

        if (entry.pwdVisible) {
            entry.pwdVisible = false;
            entry.displayPwd = "*******";
        } else {
            entry.pwdVisible = true;
            entry.displayPwd = entry.password;
        }

        m_model->editEntry(entry, row);
    });

}

VaultListPage::~VaultListPage()
{
    delete ui;
}

//add button -> initiate add dialog
void VaultListPage::on_addBtn_clicked() {
    ui->listErrorMsg->setText("");
    AddEntryDialog* addDialog = new AddEntryDialog(m_vault, this);

    connect(addDialog, &AddEntryDialog::entryAdded, this, [=](const VaultEntry& entry) {
        m_model->addEntry(entry);
        qDebug() << "calling add entry encrypt()" << m_vault->entries()[0].name;
        m_vault->encrypt();
    });
    addDialog->show();
}

void VaultListPage::on_editBtn_clicked() {
    QModelIndexList indexList = ui->vaultTableView->selectionModel()->selectedRows();
    if (indexList.size() > 0) {
        ui->listErrorMsg->setText("");
        int row = indexList.first().row();
        VaultEntry* selected = &m_vault->entries()[row];

        EditEntryDialog* editDialog = new EditEntryDialog(selected, this);

        editDialog->show();
        connect(editDialog, &EditEntryDialog::updateEntry, this, [=](const VaultEntry& entry) {
            m_model->editEntry(entry, row);
            qDebug() << "calling edit entry encrypt()";
            m_vault->encrypt();
        });
    } else {
        ui->listErrorMsg->setText("Select an entry to edit or delete it.");
        ui->listErrorMsg->show();
        ui->listErrorMsg->raise();
    }
}

void VaultListPage::on_deleteBtn_clicked() {
    QModelIndexList indexList = ui->vaultTableView->selectionModel()->selectedRows();
    if (indexList.size() > 0) {
        ui->listErrorMsg->setText("");
        int row = indexList.first().row();

        ConfirmDeleteDialog* deleteDialog = new ConfirmDeleteDialog(row, m_vault, this);

        deleteDialog->show();
        connect(deleteDialog, &ConfirmDeleteDialog::itemDeleted, this, [=](int row) {
            m_model->deleteEntry(row);
            qDebug() << "calling delete button encrypt()";
            m_vault->encrypt();
        });
    } else {
        ui->listErrorMsg->setText("Select an entry to edit or delete it.");
        ui->listErrorMsg->show();
        ui->listErrorMsg->raise();
    }
}
