#include "Vault.h"
#include <QDataStream>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <sodium.h>

Vault::Vault() {}

Vault::Vault(QByteArray key) {
    m_key = key;
}

Vault::~Vault()
{
    for (VaultEntry& entry : m_entries)
    {
        entry.clear();
    }
    m_entries.clear();
}

bool Vault::loadEncrypted() {
    //file to bytearray
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    QFile store(path + "/store.bin");

    if (store.size() == 0 || !store.exists()) {
        return false;
    }

    if (!store.open(QIODevice::ReadOnly)) return false;
    QByteArray encryptedBytes = store.readAll();
    store.close();


    QByteArray decryptData = decrypt(encryptedBytes);
    int result = decryptData.front();
    QByteArray plainTxt = decryptData.sliced(1);


    if (result != 0) {
        return false;
    }

    QDataStream input(&plainTxt, QIODevice::ReadOnly);

    m_entries.clear();

    if (plainTxt.at(0) != static_cast<char>(0xAA) && plainTxt.size() > 1 ) {
        while(!input.atEnd()) {
            VaultEntry current;
            input >> current;
            if (input.status() != QDataStream::Ok) return false;
            m_entries.append(current);
        }
    }


    return true;
}

bool Vault::encrypt() {
    QByteArray plainTxt;
    QDataStream output(&plainTxt, QIODevice::WriteOnly);

    if (m_entries.size() < 1) { // no entries -> encrypt magic byte
        output << (quint8)0xAA;
    } else { //encrypt entries
        for (VaultEntry& entry : m_entries)
        {
            output << entry;
        }
    }


    //===================ENCRYPT HERE ==========================

    unsigned char nonce[crypto_aead_chacha20poly1305_ietf_NPUBBYTES];
    const unsigned char* key = reinterpret_cast<const unsigned char*>(m_key.data());
    const unsigned char* message = reinterpret_cast<const unsigned char*>(plainTxt.data());
    const unsigned long long messageLen = plainTxt.size();
    const size_t cipherFirstSize = messageLen + crypto_aead_chacha20poly1305_ietf_ABYTES;
    QByteArray ciphertext(cipherFirstSize, 0);
    unsigned long long ciphertext_len = 0;


    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    QFile store(path + "/store.bin");
    if (!store.exists()) {
        //if never before encrypted -> create new random val
        randombytes_buf(nonce, sizeof(nonce));
    } else if (store.size() >= crypto_aead_chacha20poly1305_ietf_NPUBBYTES) {
        //if existing nonce -> increment
        if (!store.open(QIODevice::ReadOnly)) return false;
        QByteArray nonceBytes = store.read(crypto_aead_chacha20poly1305_ietf_NPUBBYTES);
        store.close();
        memcpy(nonce, nonceBytes.constData(), crypto_aead_chacha20poly1305_ietf_NPUBBYTES);
        sodium_increment(nonce, crypto_aead_chacha20poly1305_ietf_NPUBBYTES);
    }

    int success = crypto_aead_chacha20poly1305_ietf_encrypt(reinterpret_cast<unsigned char*>(ciphertext.data()),
                                  &ciphertext_len,
                                  message,
                            messageLen,
                              NULL, 0,
                              NULL, nonce, key);

    if (success != 0) return false;
    if (cipherFirstSize != ciphertext_len) return false;

    QByteArray encrypted = QByteArray();
    encrypted.append(reinterpret_cast<const char*>(nonce), crypto_aead_chacha20poly1305_ietf_NPUBBYTES);
    encrypted.append(ciphertext);

    if (!store.open(QIODevice::WriteOnly)) return false;
    store.write(encrypted);
    store.close();
    return true;
}

QByteArray Vault::decrypt(QByteArray encrypted) {
    if (encrypted.size() < crypto_aead_chacha20poly1305_ietf_NPUBBYTES + crypto_aead_chacha20poly1305_ietf_ABYTES) {
        return QByteArray(1, -1); //error with encrypted bytearray, return fail code
    }

    //===================DECRYPT HERE ==========================
        QByteArray nonce = encrypted.sliced(0, crypto_aead_chacha20poly1305_ietf_NPUBBYTES);
        QByteArray cipherText = encrypted.sliced(crypto_aead_chacha20poly1305_ietf_NPUBBYTES);
        const unsigned long long ciphertext_len = cipherText.size();
        QByteArray decrypted(ciphertext_len, 0);
        unsigned long long decrypted_len = 0;
        const unsigned char* key = reinterpret_cast<const unsigned char*>(m_key.data());

        int success = crypto_aead_chacha20poly1305_ietf_decrypt(reinterpret_cast<unsigned char*>(decrypted.data()), &decrypted_len,
                                            NULL,
                                            reinterpret_cast<const unsigned char*>(cipherText.data()),
                                            ciphertext_len,
                                            NULL,
                                            0,
                                            reinterpret_cast<const unsigned char*>(nonce.data()),
                                            key);
    if (success != 0) {
        return QByteArray(1, -1); //decrypt failed, return fail code
    }
    decrypted.resize(decrypted_len);
    return QByteArray(decrypted).prepend(success); //success, prepend with success code
}

bool Vault::addEntry(QString addName, QString addUser, QString addPwd) {
    if (addName == "" || addUser == "" || addPwd == "") return false;
    quint64 current = m_entries.empty() ? 0 : m_entries[m_entries.size() - 1].id;
    quint64 id = current + 1;
    VaultEntry newEntry = VaultEntry(id, addName, addUser, addPwd);
    m_entries.append(newEntry);
    return true;
}

void Vault::deleteEntry(int index) {
    m_entries.removeAt(index);
}

bool Vault::setKey(QByteArray key) {
    if (key.size() == 32) {
        m_key = key;
        return true;
    }
    return false;
}

const QVector<VaultEntry>& Vault::entries() const {
    return m_entries;
}

QVector<VaultEntry>& Vault::entries() {
    return m_entries;
}
