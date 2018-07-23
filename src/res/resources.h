#ifndef RESOURCES_H
#define RESOURCES_H
#include <QFont>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QString>

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
#define OS_MOBILE 1
#else
#define OS_MOBILE 0
#endif


namespace res {
    const QString configFilename {QStandardPaths::writableLocation(QStandardPaths::StandardLocation::ConfigLocation) + "/password-management.conf"};
    inline QString getDataPath() {
        QFile configFile {configFilename};
        if (configFile.open(QIODevice::ReadOnly)) {
            QString dataPath = configFile.readLine();
            if (dataPath != "" && QDir(dataPath).exists())
                return dataPath;
        }

        return
        #if OS_MOBILE
            static_cast<QString>(getenv("EXTERNAL_STORAGE") ? getenv("EXTERNAL_STORAGE") : QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation))
        #elif defined(Q_OS_LINUX)
            QStandardPaths::writableLocation(QStandardPaths::StandardLocation::HomeLocation)
        #else
            QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation)
        #endif
            + "/.password-management/";
    }
    const QString dataPath = getDataPath();



    constexpr int toolButtonsFontSize {(OS_MOBILE ? 35 : 15)};
    const QFont iconFont {"Bitstream Charter", toolButtonsFontSize};



    //s stands for "settings" and p for "password"
    namespace json {
        constexpr const char * basicStructure {R"json({"settings": {}, "passwords": []})json"};
        constexpr const char * settingsStructure {R"json({"language": %1, "pwnedActive": %2})json"};
        constexpr const char * passwordStructure {R"json({"name": "%1", "password": "%2", "email": "%3", "username": "%4", "description": "%5"})json"};
        constexpr const char * settings {"settings"};
        constexpr const char * sLanguage {"language"};
        constexpr const char * sPwnedActive {"pwnedActive"};
        constexpr const char * passwordArray {"passwords"};
        constexpr const char * pName {"name"};
        constexpr const char * pPassword {"password"};
        constexpr const char * pEmail {"email"};
        constexpr const char * pUsername {"username"};
        constexpr const char * pDescription {"description"};
    }



	enum class Lang : char {
        en, it
    };
	inline constexpr uint qHash(const Lang& lang) {
		return static_cast<uint>(lang);
	}


	using lhpair = std::pair<Lang, QHash<QString, QString>>;
	using sspair = QHash<QString, QString>;
	const QHash<Lang, QHash<QString, QString>> loginCaptions {
		lhpair{Lang::it, sspair{
				{"hello", "ciao"},
				{"hi", "ehi"}
			}}
	};
}

#endif // RESOURCES_H
