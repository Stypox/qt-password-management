#include "password.h"
#include "resources.h"
#include <QJsonDocument>

using namespace json;

Password::Password() {}
Password::Password(const QJsonObject& passwordJson) :
    name {passwordJson[pName].toString()},
    password {passwordJson[pPassword].toString()},
    email {passwordJson[pEmail].toString()},
    username {passwordJson[pUsername].toString()},
    description {passwordJson[pDescription].toString()} {}
void Password::operator() (const QJsonObject &passwordJson) {
    name = passwordJson[pName].toString();
    password = passwordJson[pPassword].toString();
    email = passwordJson[pEmail].toString();
    username = passwordJson[pUsername].toString();
    description = passwordJson[pDescription].toString();
}

QJsonObject Password::toJson() const {
    QString passwordJson {passwordStructure};
    return QJsonDocument::fromJson(passwordJson.arg(name, password, email, username, description).toUtf8()).object();
}
