#include "VaultEntry.h"

VaultEntry::VaultEntry() {
    id = 0;
    name = "";
    username = "";
    displayPwd = "********";
    password = "";
    pwdVisible = false;
}

VaultEntry::VaultEntry(quint64 addId, QString addName, QString addUser, QString addPwd) {
    id = addId;
    name = addName;
    username = addUser;
    displayPwd = "********";
    password = addPwd;
    pwdVisible = false;
}

void VaultEntry::clear() {
    name.clear();
    username.clear();
    displayPwd = "********";
    password.clear();
    pwdVisible = false;
}

QDataStream& operator>>(QDataStream& in, VaultEntry& entry) {
    in >> entry.id >> entry.name >> entry.username >> entry.password;
    return in;
}

QDataStream& operator<<(QDataStream& out, const VaultEntry& entry) {
    out << entry.id << entry.name << entry.username << entry.password;
    return out;
}
