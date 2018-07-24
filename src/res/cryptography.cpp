#include "cryptography.h"
#include <QVector>
#include <QDebug>

namespace res {
	//key HAS to be of length keyLen=32. If more, only first 32 chars are considered
	QVector<quint64> splitKey(const QByteArray& key) {
		auto chars = reinterpret_cast<const unsigned char *>(key.data());
		QVector<quint64> result(4, 0);
		for (int offset = 0; offset < 4; ++offset) {
			for (int keyIndex = 0; keyIndex < 8; ++keyIndex) {
				result[offset] |= ((quint64{0} | chars[keyIndex * 4 + offset]) << (keyIndex * 8));
			}
		}
		return result;
	}

	//password HAS to be of length >= 8
	QByteArray encrypt(QByteArray decryptedData, const QByteArray& password) {
		QByteArray salt {};
		for (int saltChar = 0; saltChar < res::saltLen; ++saltChar) {
			salt += qrand() % 256;
		}

		QVector<quint64> keys = splitKey(password + salt);

		for (auto&& key : keys)
			decryptedData = SimpleCrypt(key).encryptToByteArray(decryptedData);

		return salt + decryptedData;
	}

	//password HAS to be of length >= 8
	QByteArray decrypt(QByteArray encryptedData, const QByteArray& password, SimpleCrypt::Error& success) {
		QByteArray salt {encryptedData.left(res::saltLen)};
		encryptedData.remove(0, res::saltLen);

		QVector<quint64> keys = splitKey(password + salt);

		SimpleCrypt cryptEngine {keys[0]};
		cryptEngine.decryptToByteArray(encryptedData);
		success = cryptEngine.lastError();
		for (auto it = keys.rbegin() + 1; it < keys.rend(); ++it)
			encryptedData = SimpleCrypt{*it}.decryptToByteArray(encryptedData);

		return encryptedData;
	}
}
