#ifndef EDITENTRYDIALOG_H
#define EDITENTRYDIALOG_H

#include <QDialog>
#include "VaultEntry.h"

namespace Ui {
class EditEntryDialog;
}

class EditEntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditEntryDialog(VaultEntry* entry, QWidget *parent = nullptr);
    ~EditEntryDialog();

signals:
    void updateEntry(const VaultEntry& updEntry);

private:
    Ui::EditEntryDialog *ui;
    VaultEntry *m_entry;

private slots:
void on_eBtn_clicked();
void on_eCancelBtn_clicked();
};

#endif // EDITENTRYDIALOG_H
