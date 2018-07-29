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
	inline void operator++(Lang& lang) {
		lang = static_cast<Lang>(static_cast<int>(lang) + 1);
	}
	constexpr unsigned int qHash(const Lang& lang) {
		return static_cast<unsigned int>(lang);
	}

	class Config {
	public:
		Config();
		~Config();

		const QString& dataDir() const;
		const Lang& language() const;
		void setLanguage(const Lang& language);
	//private:
		void save() const;

		const QString m_filename;
		const QString m_directory;
		Lang m_language;
	};
	extern Config config;

	constexpr const char * dataFileExt = ".txt";
	constexpr const char * backupFileExt = ".bak";

	constexpr int iconFontSize {(OS_MOBILE ? 35 : 15)};
	const QFont iconFont {"Bitstream Charter", iconFontSize};
	constexpr int passwordWidgetClosedHeight{(OS_MOBILE ? 150 : 45)};
	constexpr int passwordWidgetOpenedHeight{(OS_MOBILE ? 400 : 140)};

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
				{"yes", "Yes"},
				{"no", "No"},
			}
		},
		{
			Lang::it, {
				{"langName", "Italiano"},
				{"yes", QString::fromWCharArray(L"Sì")},
				{"no", "No"},
			}
		},
	};
	const QHash<Lang, QHash<QString, QString>> passwordsLabels {
		{
			Lang::en, {
				{"windowTitle", "Password management"},
				{"usernameDefault", ""},
				{"questionRemovalTitle", "Removing %1..."},
				{"questionRemoval", "Do you really want to remove password %1?"},
			}
		},
		{
			Lang::it, {
				{"windowTitle", "Gestione password"},
				{"usernameDefault", ""},
				{"questionRemovalTitle", "Rimuovendo %1..."},
				{"questionRemoval", "Vuoi davvero rimuovere la password %1?"},
			}
		},
	};
	const QHash<Lang, QHash<QString, QString>> loginLabels {
		{
			Lang::en, {
				{"windowTitle", "Login"},
				{"usernameTitle", "Username:"},
				{"passwordTitle", "Password:"},
				{"create", "Create"},
				{"login", "Login"},
				{"noError", ""},
				{"noWarning", ""},
				{"errInvalidPassword", "Password length is between 8 and 31"},
				{"errFileNotFound", "This account doesn't exist"},
				{"errCorruptedFile", "Corrupted file: unable to decrypt"},
				{"errCorruptedData", "The decrypted data is corrupted"},
				{"errInvalidFile", "Wrong password or corrupted file"},
				{"errPasswordsNotMatching", "Passwords do not match"},
				{"errExistingAccount", "Account already exists: the old one will be backupped"},
				{"warReinsertPassword", "Reinsert password"},
			}
		},
		{
			Lang::it, {
				{"windowTitle", "Accesso"},
				{"usernameTitle", "Username:"},
				{"passwordTitle", "Password:"},
				{"create", "Crea"},
				{"login", "Accedi"},
				{"noError", ""},
				{"errInvalidPassword", QString::fromWCharArray(L"Password è lunga tra 8 e 31")},
				{"errFileNotFound", "Quest'account non esiste"},
				{"errCorruptedFile", "File corrotto"},
				{"errCorruptedData", "I dati decriptati sono corrotti"},
				{"errInvalidFile", "Password errata o file corrotto"},
				{"errPasswordsNotMatching", "Le password non corrispondono"},
				{"errExistingAccount", QString::fromWCharArray(L"L'account esiste già: il vecchio sarà backuppato")},
				{"warReinsertPassword", "Reinserisci la password"},
			}
		},
	};
	const QHash<Lang, QHash<QString, QString>> addEditLabels {
		{
			Lang::en, {
				{"editPassword", "Edit password"},
				{"newPassword", "New password"},
				{"nameTitle", "Name:"},
				{"passwordTitle", "Password:"},
				{"emailTitle", "Email:"},
				{"usernameTitle", "Username:"},
				{"ok", "Ok"},
				{"cancel", "Cancel"},
			}
		},
		{
			Lang::it, {
				{"editPassword", "Modifica password"},
				{"newPassword", "Nuova password"},
				{"nameTitle", "Nome:"},
				{"passwordTitle", "Password:"},
				{"emailTitle", "Email:"},
				{"usernameTitle", "Username:"},
				{"ok", "Ok"},
				{"cancel", "Annulla"},
			}
		},
	};
	const QHash<Lang, QHash<QString, QString>> widgetLabels {
		{
			Lang::en, {
				{"passwordTitle", "Password: "},
				{"emailTitle", "Email: "},
				{"usernameTitle", "Username: "},
			}
		},
		{
			Lang::it, {
				{"passwordTitle", "Password: "},
				{"emailTitle", "Email: "},
				{"usernameTitle", "Username: "},
			}
		},
	};

	void debug();
}

#endif // RESOURCES_H
