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
	constexpr int saltLen = 24,
		keyLen = 32,
		passwordMinLen = keyLen - saltLen,
		passwordMaxLen = keyLen - 1;

	enum class Lang : char {
		en, it,
		min = en, max = it, def = en,
	};
	constexpr unsigned int qHash(const Lang& lang) {
		return static_cast<unsigned int>(lang);
	}

	class Config {
	public:
		Config();
		~Config();
		void save() const;

		const QString& dataPath() const;
		const Lang& language() const;
	private:
		const QString m_filename;
		const QString m_directory;
		QString m_dataPath;
		Lang m_language;
	};
	const Config config;

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

	const QHash<Lang, QHash<QString, QString>> sharedLabels {
		{
			Lang::en, {
				{"langName", "English"},
				{"", ""},
			}
		},
		{
			Lang::it, {
				{"langName", "Italiano"},
			}
		},
	};
	const QHash<Lang, QHash<QString, QString>> loginLabels {
		{
			Lang::en, {
				{"username", "Username"},
				{"password", "Password"},
				{"create", "Create"},
				{"login", "Login"},
				{"reinsert", "Reinsert"},
				{"noError", ""},
				{"errFileNotFound", "This account doesn't exist"},
				{"errCorruptedFile", "Corrupted file"},
				{"errInvalidFile", "Wrong password or corrupted file"},
				{"errPasswordsNotMatching", "Passwords do not match"},
				{"errExistingAccount", "This account already exists"},
			}
		},
		{
			Lang::it, {
				{"username", "Nome utente"},
				{"password", "Password"},
				{"create", "Crea"},
				{"login", "Entra"},
				{"reinsert", "Reinserisci"},
				{"noError", ""},
				{"errFileNotFound", "Quest'account non esiste"},
				{"errCorruptedFile", "File corrotto"},
				{"errInvalidFile", "Password errata o file corrotto"},
				{"errPasswordsNotMatching", "Le password non corrispondono"},
				{"errExistingAccount", "Quest'account esiste gia'"},
			}
		},
	};

	void debug();
}

#endif // RESOURCES_H
