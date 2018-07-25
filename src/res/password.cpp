#include "password.h"
#include "resources.h"
#include <QJsonDocument>

using namespace res;

Password::Password() {}
Password::Password(const QJsonObject& passwordJson) :
	name {passwordJson[json::pName].toString()},
	password {passwordJson[json::pPassword].toString()},
	email {passwordJson[json::pEmail].toString()},
	username {passwordJson[json::pUsername].toString()},
	description {passwordJson[json::pDescription].toString()} {}

QJsonObject Password::toJson() const {
	QString passwordJson {json::passwordStructure};
	passwordJson = passwordJson.arg(name).arg(password).arg(email).arg(username).arg(description);
	return QJsonDocument::fromJson(passwordJson.toUtf8()).object();
}
