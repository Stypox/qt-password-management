#ifndef SETTINGS_H
#define SETTINGS_H
#include <QJsonObject>
#include "resources.h"

struct Settings {
    Settings();
    Settings(const QJsonObject& settingsJson);
    void operator()(const QJsonObject& settingsJson);

    QJsonObject toJson() const;

    Lang language;
    bool pwnedActive;
};

#endif // SETTINGS_H