#include "settings.h"
#include <QJsonDocument>

using namespace res;

Settings::Settings() {}
Settings::Settings(const QJsonObject& settingsJson) :
    language {static_cast<Lang>(settingsJson[json::sLanguage].toInt())},
    pwnedActive {settingsJson[json::sPwnedActive].toBool()} {}
void Settings::operator()(const QJsonObject& settingsJson) {
    language = static_cast<Lang>(settingsJson[json::sLanguage].toInt());
    pwnedActive = settingsJson[json::sPwnedActive].toBool();
}

QJsonObject Settings::toJson() const {
    QString settingsJson {json::settingsStructure};
    return QJsonDocument::fromJson(settingsJson.arg(QString::number(static_cast<int>(language)), pwnedActive).toUtf8()).object();
}
