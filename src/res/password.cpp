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
void Password::operator() (const QJsonObject &passwordJson) {
    name = passwordJson[json::pName].toString();
    password = passwordJson[json::pPassword].toString();
    email = passwordJson[json::pEmail].toString();
    username = passwordJson[json::pUsername].toString();
    description = passwordJson[json::pDescription].toString();
}

QJsonObject Password::toJson() const {
    QString passwordJson {json::passwordStructure};
    return QJsonDocument::fromJson(passwordJson.arg(name, password, email, username, description).toUtf8()).object();
}
