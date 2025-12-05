#ifndef VAULT_H
#define VAULT_H

#include "VaultEntry.h"
#include <QVector>
#include <QString>
#include <QByteArray>
#include <qstringview.h>

class Vault
{
public:
    Vault();
    Vault(QByteArray key);
    ~Vault();
    bool loadEncrypted();
    bool encrypt();
    QByteArray decrypt(QByteArray encrypted);
    bool addEntry(QString addName, QString addUser, QString addPwd);
    void deleteEntry(int index);
    bool setKey(QByteArray key);
    const QVector<VaultEntry>& entries() const;
    QVector<VaultEntry>& entries();

private:
    QVector<VaultEntry> m_entries;
    QByteArray m_key;
};

#endif // VAULT_H
