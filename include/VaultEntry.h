#ifndef VAULTENTRY_H
#define VAULTENTRY_H

#include <QString>
#include <QDataStream>

struct VaultEntry {
    quint64 id;
    QString name;
    QString username;
    QString displayPwd;
    QString password;
    bool pwdVisible;

    VaultEntry();
    VaultEntry(quint64 addId, QString addName, QString addUser, QString addPwd);

    void clear();
};

QDataStream& operator>>(QDataStream& in, VaultEntry& entry);
QDataStream& operator<<(QDataStream& out, const VaultEntry& entry);


#endif // VAULTENTRY_H
