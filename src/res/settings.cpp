#include "settings.h"
#include <QJsonDocument>
#include <QDebug>

Settings::Settings() : loaded(false) {}

void Settings::load(const QString& Username, const QByteArray& Password, const QJsonObject& settingsJson) {
	loaded = true;
	username = Username;
	password = Password;

	language = static_cast<res::Lang>(settingsJson[res::json::sLanguage].toInt());
	pwnedActive = settingsJson[res::json::sPwnedActive].toBool();
}
void Settings::load(const QString& Username, const QByteArray& Password, const res::Lang& Language, const bool& PwnedActive) {
	loaded = true;
	username = Username;
	password = Password;
	language = Language;
	pwnedActive = PwnedActive;
}
QByteArray Settings::toJson() const {
	QString settingsJson {res::json::settingsStructure};
	settingsJson = settingsJson.arg(static_cast<int>(language)).arg(pwnedActive ? "true" : "false");
	return settingsJson.toUtf8();
}

void Settings::reset() {
	loaded = false;
}

void Settings::debug() {
	qDebug() << "Settings    Username:" << username << " Key:" << password << " Language:" << static_cast<int>(language) << " Pwned:" << pwnedActive << " Json:" << toJson();
}
