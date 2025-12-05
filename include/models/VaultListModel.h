#ifndef VAULTLISTMODEL_H
#define VAULTLISTMODEL_H
#include <QAbstractTableModel>
#include <VaultEntry.h>

class VaultListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit VaultListModel(QObject *parent = nullptr);

    void setEntries(const QVector<VaultEntry> &entries);

    int columnCount(const QModelIndex&) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    void addEntry(const VaultEntry &entry);

    void editEntry(const VaultEntry &entry, int row);

    void deleteEntry(int row);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    const VaultEntry& findEntry(int index) const;


private:
    QVector<VaultEntry> m_entries;
};

#endif // VAULTLISTMODEL_H
