#ifndef PASSWORDSTRUCTURE_H
#define PASSWORDSTRUCTURE_H
#include <QObject>
#include <QString>
#include <QVector>
#include <QJsonObject>


struct Password {
	Password();
	Password(const QJsonObject&passwordJson);

	QJsonObject toJson() const;

	QString name;
	QString password;
	QString email;
	QString username;
	QString description;
};

#endif // PASSWORDSTRUCTURE_H
