#ifndef SETTINGS_H
#define SETTINGS_H
#include <QJsonObject>
#include "resources.h"

struct Settings {
	Settings();

	void load(const QString& Username, const QByteArray& Password, const QJsonObject& settingsJson);
	void load(const QString& Username, const QByteArray& Password, const res::Lang& Language = res::Lang::def, const bool& PwnedActive = false);
	QByteArray toJson() const;
	void reset();

	void debug();

	bool loaded;

	QString username;
	QByteArray password;
	res::Lang language;
	bool pwnedActive;
};

#endif // SETTINGS_H
