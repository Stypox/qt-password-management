#ifndef PASSWORDSTRUCTURE_H
#define PASSWORDSTRUCTURE_H
#include <QObject>
#include <QString>
#include <QVector>
#include <QJsonObject>


struct PasswordStructure : public QObject {
    PasswordStructure(QJsonObject json);

    QJsonObject toJson();

    QString m_name;
    QString m_password;
    QString m_email;
    QVector<QString> m_usernames;
    QString m_description;
};

#endif // PASSWORDSTRUCTURE_H
