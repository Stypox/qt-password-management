#include "settings.h"
#include <QJsonDocument>

using namespace json;

Settings::Settings() {}
Settings::Settings(const QJsonObject& settingsJson) :
    language {static_cast<Lang>(settingsJson[sLanguage].toInt())},
    pwnedActive {settingsJson[sPwnedActive].toBool()} {}
void Settings::operator()(const QJsonObject& settingsJson) {
    language = static_cast<Lang>(settingsJson[sLanguage].toInt());
    pwnedActive = settingsJson[sPwnedActive].toBool();
}

QJsonObject Settings::toJson() const {
    QString settingsJson {settingsStructure};
    return QJsonDocument::fromJson(settingsJson.arg(QString::number(static_cast<int>(language)), pwnedActive).toUtf8()).object();
}
