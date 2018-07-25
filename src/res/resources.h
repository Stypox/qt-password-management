#ifndef RESOURCES_H
#define RESOURCES_H
#include <QFont>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QString>
#include "settings.h"
#include "password.h"

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

		const QString& dataDir() const;
		const Lang& language() const;
	private:
		const QString m_filename;
		const QString m_directory;
		QString m_dataPath;
		Lang m_language;
	};
	const Config config;

	constexpr const char * dataFileExt = ".txt";
	constexpr const char * backupFileExt = ".bak";

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
				{"usernameTitle", "Username:"},
				{"passwordTitle", "Password:"},
				{"create", "Create"},
				{"login", "Login"},
				{"noError", ""},
				{"errInvalidPassword", "Password length is between 8 and 31"},
				{"errFileNotFound", "This account doesn't exist Quest'account esiste gia', verrà creato un backup"},
				{"errCorruptedFile", "Corrupted file: unable to decrypt"},
				{"errCorruptedData", "The decrypted data is corrupted"},
				{"errInvalidFile", "Wrong password or corrupted file"},
				{"errPasswordsNotMatching", "Passwords do not match"},
				{"warExistingAccount", "Backupped the old account"},
				{"warReinsertPassword", "Reinsert password"},
			}
		},
		{
			Lang::it, {
				{"usernameTitle", "Nome utente"},
				{"passwordTitle", "Password"},
				{"create", "Crea"},
				{"login", "Entra"},
				{"noError", ""},
				{"errInvalidPassword", "Password e' lunga tra 8 e 31"},
				{"errFileNotFound", "Quest'account non esiste"},
				{"errCorruptedFile", "File corrotto"},
				{"errCorruptedData", "I dati decriptati sono corrotti"},
				{"errInvalidFile", "Password errata o file corrotto"},
				{"errPasswordsNotMatching", "Le password non corrispondono"},
				{"warExistingAccount", "Fatto il backup del vecchio account"},
				{"warReinsertPassword", "Reinserisci la password"},
			}
		},
	};

	void debug();
}

#endif // RESOURCES_H
