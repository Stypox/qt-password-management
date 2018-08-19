#include "settings.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

Settings::Settings() : loaded(false) {}

bool Settings::load(const QJsonObject& settingsJson) {
	language = static_cast<res::Lang>(settingsJson[res::json::sLanguage].toInt(static_cast<int>(res::Lang::max) + 1));
	if (language > res::Lang::max || language < res::Lang::min)
		language = res::Lang::def;

	if (!settingsJson.contains(res::json::sReorderingActive) || !settingsJson[res::json::sReorderingActive].isBool())
		reorderingActive = false;
	else
		reorderingActive = settingsJson[res::json::sReorderingActive].toBool();

	if (!settingsJson.contains(res::json::sDarkThemeActive) || !settingsJson[res::json::sDarkThemeActive].isBool())
		darkThemeActive = false;
	else
		darkThemeActive = settingsJson[res::json::sDarkThemeActive].toBool();

	if (!settingsJson.contains(res::json::sRemovalConfirmationDialogActive) || !settingsJson[res::json::sRemovalConfirmationDialogActive].isBool())
		removalConfirmationDialogActive = true;
	else
		removalConfirmationDialogActive = settingsJson[res::json::sRemovalConfirmationDialogActive].toBool();

	if (!settingsJson.contains(res::json::sPwnedActive) || !settingsJson[res::json::sPwnedActive].isBool())
		pwnedActive = false;
	else
		pwnedActive = settingsJson[res::json::sPwnedActive].toBool();

	loaded = true;
	return true;
}
bool Settings::load(const res::Lang& Language, const bool& ReorderingActive, const bool& DarkThemeActive, const bool& RemovalConfirmationDialogActive, const bool& PwnedActive) {
	language = Language;
	if (language > res::Lang::max || language < res::Lang::min)
		return false;

	reorderingActive = ReorderingActive;
	darkThemeActive = DarkThemeActive;
	removalConfirmationDialogActive = RemovalConfirmationDialogActive;
	pwnedActive = PwnedActive;

	loaded = true;
	return true;
}
QJsonValue Settings::toJson() const {
	if (!loaded)
		return QJsonValue{};
	QString settingsJson {res::json::settingsStructure};
	settingsJson = settingsJson.arg(static_cast<int>(language))
			.arg(reorderingActive ? "true" : "false")
			.arg(darkThemeActive ? "true" : "false")
			.arg(removalConfirmationDialogActive ? "true" : "false")
			.arg(pwnedActive ? "true" : "false");

	return QJsonDocument::fromJson(settingsJson.toUtf8()).object();
}
void Settings::reset() {
	loaded = false;
}

void Settings::debug() const {
	qDebug() << "Settings:    "
			 << " language:" << static_cast<int>(language)
			 << " reorderingActive:" << reorderingActive
			 << " darkThemeActive:" << darkThemeActive
			 << " removalConfirmationDialogActive:" << removalConfirmationDialogActive
			 << " pwnedActive:" << pwnedActive
			 << " json:" << QJsonDocument{toJson().toObject()}.toJson(QJsonDocument::JsonFormat::Compact);
}


bool extractData(const QByteArray& dataJson, Settings& settings, QVector<Password>& passwords) {
	settings.reset();
	passwords.resize(0);

	QJsonDocument dataDocument = QJsonDocument::fromBinaryData(dataJson);
	qDebug() << dataDocument.toJson(QJsonDocument::JsonFormat::Compact);
	if (!dataDocument.isObject()) {
		settings.loaded = false;
		return false;
	}
	QJsonObject data {dataDocument.object()};
	if (!data.contains(res::json::settings) || !data[res::json::settings].isObject() ||
			!data.contains(res::json::passwordArray) || !data[res::json::passwordArray].isArray()) {
		settings.loaded = false;
		return false;
	}

	settings.load(data[res::json::settings].toObject());
	for (auto passwordJson : data[res::json::passwordArray].toArray()) {
		Password password;
		if (!passwordJson.isObject() ||
				!password.load(passwordJson.toObject())) {
			settings.loaded = false;
			return false;
		}
		passwords.push_back(password);
	}
	return true;
}
QByteArray buildData(const Settings& settings, const QVector<Password>& passwords) {
	QJsonObject data {QJsonDocument::fromJson(res::json::basicStructure).object()};

	data[res::json::settings] = settings.toJson();
	QJsonArray passwordsJsonArray{};
	for (auto&& password : passwords)
		passwordsJsonArray.push_back(password.toJson());
	data[res::json::passwordArray] = passwordsJsonArray;

	return QJsonDocument{data}.toBinaryData();
}
