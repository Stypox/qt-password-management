#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <QByteArray>
#include "resources.h"
#include "src/simplecrypt/simplecrypt.h"

namespace res {
	QVector<quint64> splitKey(const QByteArray& key);

	QByteArray encrypt(QByteArray decryptedData, const QByteArray& password);
	QByteArray decrypt(QByteArray encryptedData, const QByteArray& password, SimpleCrypt::Error& success);
}

#endif // ENCRYPTION_H
