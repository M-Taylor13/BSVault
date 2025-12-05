#include "VaultListModel.h"

VaultListModel::VaultListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void VaultListModel::setEntries(const QVector<VaultEntry> &entries) {
    beginResetModel();
    m_entries = entries;
    endResetModel();
}

const VaultEntry& VaultListModel::findEntry(int index) const {
    return m_entries[index];
}

int VaultListModel::columnCount(const QModelIndex&) const {
    return 4;
}

int VaultListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return m_entries.count();
}

void VaultListModel::addEntry(const VaultEntry &entry) {
    int row = m_entries.size();
    beginInsertRows(QModelIndex(), row, row);
    m_entries.append(entry);
    endInsertRows();
}

void VaultListModel::editEntry(const VaultEntry &entry, int row) {
    m_entries[row] = entry;
    emit dataChanged(index(row,0), index(row,2));
}

void VaultListModel::deleteEntry(int row) {
    beginRemoveRows(QModelIndex(), row, row);
    m_entries.removeAt(row);
    endRemoveRows();
}

QVariant VaultListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return {};

    const VaultEntry &entry = m_entries[index.row()];

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0: return entry.name;
        case 1: return entry.username;
        case 2: return entry.displayPwd;
        case 3: return "show/hide placeholder";
        }
    }
    return {};
}
