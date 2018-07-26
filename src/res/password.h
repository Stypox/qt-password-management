#ifndef PASSWORDSTRUCTURE_H
#define PASSWORDSTRUCTURE_H
#include <QObject>
#include <QString>
#include <QVector>
#include <QJsonObject>


struct Password {
	Password();

	bool load(const QJsonObject& passwordJson);

	QJsonValue toJson() const;

	QString name;
	QString password;
	QString email;
	QString username;
	QString description;
};

#endif // PASSWORDSTRUCTURE_H
