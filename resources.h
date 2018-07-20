#ifndef RESOURCES_H
#define RESOURCES_H
#include <QFont>

#ifdef Q_OS_ANDROID
constexpr int toolButtonsFontSize = 35;
#else
constexpr int toolButtonsFontSize = 15;
#endif
const QFont toolButtonsFont {"Bitstream Charter", toolButtonsFontSize};

enum class Lang {
    en, it
};

/*
s stands for "settings" and p for "password"
*/
namespace json {
    constexpr const char * basicStructure = R"json({"settings": {}, "passwords": []})json";
    constexpr const char * settingsStructure = R"json({"language": %1, "pwnedActive": %2})json";
    constexpr const char * passwordStructure = R"json({"name": "%1", "password": "%2", "email": "%3", "username": "%4", "description": "%5"})json";
    constexpr const char * settings = "settings";
    constexpr const char * sLanguage = "language";
    constexpr const char * sPwnedActive = "pwnedActive";
    constexpr const char * PasswordArray = "passwords";
    constexpr const char * pName = "name";
    constexpr const char * pPassword = "password";
    constexpr const char * pEmail = "email";
    constexpr const char * pUsername = "username";
    constexpr const char * pDescription = "description";
}

#endif // RESOURCES_H
