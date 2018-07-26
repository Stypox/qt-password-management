#include "password.h"
#include "resources.h"
#include <QJsonDocument>

Password::Password() {}
bool Password::load(const QJsonObject& passwordJson) {
	if (!passwordJson.contains(res::json::pName) || !passwordJson[res::json::pName].isString() ||
			!passwordJson.contains(res::json::pPassword) || !passwordJson[res::json::pPassword].isString() ||
			!passwordJson.contains(res::json::pEmail) || !passwordJson[res::json::pEmail].isString() ||
			!passwordJson.contains(res::json::pUsername) || !passwordJson[res::json::pUsername].isString() ||
			!passwordJson.contains(res::json::pDescription) || !passwordJson[res::json::pDescription].isString())
		return false;

	name = passwordJson[res::json::pName].toString();
	password = passwordJson[res::json::pPassword].toString();
	email = passwordJson[res::json::pEmail].toString();
	username = passwordJson[res::json::pUsername].toString();
	description = passwordJson[res::json::pDescription].toString();
	return true;
}

QJsonValue Password::toJson() const {
	QString passwordJson {res::json::passwordStructure};
	passwordJson = passwordJson.arg(name).arg(password).arg(email).arg(username).arg(description);

	return QJsonDocument::fromJson(passwordJson.toUtf8()).object();
}
