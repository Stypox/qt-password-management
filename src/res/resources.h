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
	private:
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

	constexpr Qt::InputMethodHints inputMethod = Qt::ImhPreferLatin | Qt::ImhNoEditMenu | Qt::ImhNoTextHandles;

	//s stands for "settings" and p for "password"
	namespace json {
		constexpr const char * basicStructure {R"json({"settings": {}, "passwords": []})json"};
		constexpr const char * settingsStructure {R"json({"language": %1, "darkThemeActive": %2, "removalConfirmationDialogActive": %3, "pwnedActive": %4})json"};
		constexpr const char * passwordStructure {R"json({"name": "%1", "password": "%2", "email": "%3", "username": "%4", "description": "%5"})json"};
		constexpr const char * settings {"settings"};
		constexpr const char * sLanguage {"language"};
		constexpr const char * sDarkThemeActive {"darkThemeActive"};
		constexpr const char * sRemovalConfirmationDialogActive {"removalConfirmationDialogActive"};
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
				{"ok", "Ok"},
				{"cancel", "Cancel"},
				{"apply", "Apply"},
				{"noError", ""},
				{"errInvalidPassword", "Password length is between 8 and 31"},
				{"errPasswordsNotMatching", "Passwords do not match"},
				{"nameTitle", "Name"},
				{"passwordTitle", "Password"},
				{"emailTitle", "Email"},
				{"usernameTitle", "Username"},
			}
		},
		{
			Lang::it, {
				{"langName", "Italiano"},
				{"ok", "Ok"},
				{"cancel", "Annulla"},
				{"apply", "Applica"},
				{"noError", ""},
				{"errInvalidPassword", QString::fromWCharArray(L"Password è lunga tra 8 e 31")},
				{"errPasswordsNotMatching", "Le password non corrispondono"},
				{"nameTitle", "Nome"},
				{"passwordTitle", "Password"},
				{"emailTitle", "Email"},
				{"usernameTitle", "Username"},
			}
		},
	};
	const QHash<Lang, QHash<QString, QString>> passwordsLabels {
		{
			Lang::en, {
				{"windowTitle", "Password management - %1"},
				{"usernameDefault", ""},
				{"questionRemovalTitle", "Removing %1..."},
				{"questionRemoval", "Do you really want to remove password %1?"},
			}
		},
		{
			Lang::it, {
				{"windowTitle", "Gestione password - %1"},
				{"usernameDefault", ""},
				{"questionRemovalTitle", "Rimuovendo %1..."},
				{"questionRemoval", "Vuoi davvero rimuovere la password %1?"},
			}
		},
	};
	const QHash<Lang, QHash<QString, QString>> loginLabels {
		{
			Lang::en, {
				{"windowTitle", "Login - Password management"},
				{"usernameTitle", sharedLabels[Lang::en]["nameTitle"] + ":"},
				{"passwordTitle", sharedLabels[Lang::en]["passwordTitle"] + ":"},
				{"create", "Create"},
				{"login", "Login"},
				{"noError", sharedLabels[Lang::en]["noError"]},
				{"noWarning", ""},
				{"errInvalidPassword", sharedLabels[Lang::en]["errInvalidPassword"]},
				{"errFileNotFound", "This account doesn't exist"},
				{"errCorruptedFile", "Corrupted file: unable to decrypt"},
				{"errCorruptedData", "The decrypted data is corrupted"},
				{"errInvalidFile", "Wrong password or corrupted file"},
				{"errPasswordsNotMatching", sharedLabels[Lang::en]["errPasswordsNotMatching"]},
				{"errExistingAccount", "Account already exists: the old one will be backupped"},
				{"warReinsertPassword", "Reinsert password"},
			}
		},
		{
			Lang::it, {
				{"windowTitle", "Accesso - Gestione password"},
				{"usernameTitle", sharedLabels[Lang::it]["nameTitle"] + ":"},
				{"passwordTitle", sharedLabels[Lang::it]["passwordTitle"] + ":"},
				{"create", "Crea"},
				{"login", "Accedi"},
				{"noError", sharedLabels[Lang::it]["noError"]},
				{"noWarning", ""},
				{"errInvalidPassword", sharedLabels[Lang::it]["errInvalidPassword"]},
				{"errFileNotFound", "Quest'account non esiste"},
				{"errCorruptedFile", "File corrotto"},
				{"errCorruptedData", "I dati decriptati sono corrotti"},
				{"errInvalidFile", "Password errata o file corrotto"},
				{"errPasswordsNotMatching", sharedLabels[Lang::it]["errPasswordsNotMatching"]},
				{"errExistingAccount", QString::fromWCharArray(L"L'account esiste già: il vecchio sarà backuppato")},
				{"warReinsertPassword", "Reinserisci la password"},
			}
		},
	};
	const QHash<Lang, QHash<QString, QString>> addEditLabels {
		{
			Lang::en, {
				{"editPassword", "Edit password - %1"},
				{"newPassword", "New password - %1"},
				{"nameTitle", sharedLabels[Lang::en]["nameTitle"] + ":"},
				{"passwordTitle", sharedLabels[Lang::en]["passwordTitle"] + ":"},
				{"emailTitle", sharedLabels[Lang::en]["emailTitle"] + ":"},
				{"usernameTitle", sharedLabels[Lang::en]["usernameTitle"] + ":"},
			}
		},
		{
			Lang::it, {
				{"editPassword", "Modifica password - %1"},
				{"newPassword", "Nuova password - %1"},
				{"nameTitle", sharedLabels[Lang::it]["nameTitle"] + ":"},
				{"passwordTitle", sharedLabels[Lang::it]["passwordTitle"] + ":"},
				{"emailTitle", sharedLabels[Lang::it]["emailTitle"] + ":"},
				{"usernameTitle", sharedLabels[Lang::it]["usernameTitle"] + ":"},
			}
		},
	};
	const QHash<Lang, QHash<QString, QString>> widgetLabels {
		{
			Lang::en, {
				{"passwordTitle", sharedLabels[Lang::en]["passwordTitle"] + ": "},
				{"emailTitle", sharedLabels[Lang::en]["emailTitle"] + ": "},
				{"usernameTitle", sharedLabels[Lang::en]["usernameTitle"] + ": "},
			}
		},
		{
			Lang::it, {
				{"passwordTitle", sharedLabels[Lang::it]["passwordTitle"] + ": "},
				{"emailTitle", sharedLabels[Lang::it]["emailTitle"] + ": "},
				{"usernameTitle", sharedLabels[Lang::it]["usernameTitle"] + ": "},
			}
		},
	};
	const QHash<Lang, QHash<QString, QString>> settingsLabels {
		{
			Lang::en, {
				{"windowTitle", "Settings - %1"},
				{"languageTitle", "Language:"},
				{"darkThemeTitle", "Dark theme"},
				{"removalConfirmationDialogTitle", "Removal confirmation dialog"},
				{"pwnedTitle", "Have I Been Pwned"},
				{"passwordTitle", "New password:"},
				{"reinsertPasswordTitle", "Reinsert:"},
				{"backup", "Backup"},
				{"resetSettings", "Reset settings"},
				{"ok", sharedLabels[Lang::en]["ok"]},
				{"cancel", sharedLabels[Lang::en]["cancel"]},
				{"apply", sharedLabels[Lang::en]["apply"]},
				{"noError", sharedLabels[Lang::en]["noError"]},
				{"errInvalidPassword", sharedLabels[Lang::en]["errInvalidPassword"]},
				{"errPasswordsNotMatching", sharedLabels[Lang::en]["errPasswordsNotMatching"]},
			}
		},
		{
			Lang::it, {
				{"windowTitle", "Impostazioni - %1"},
				{"languageTitle", "Lingua:"},
				{"darkThemeTitle", "Tema scuro"},
				{"removalConfirmationDialogTitle", "Dialogo di conferma rimozione"},
				{"pwnedTitle", "Have I Been Pwned"},
				{"passwordTitle", "Nuova password:"},
				{"reinsertPasswordTitle", "Reinserisci:"},
				{"backup", "Backup"},
				{"resetSettings", "Reset settings"},
				{"ok", sharedLabels[Lang::it]["ok"]},
				{"cancel", sharedLabels[Lang::it]["cancel"]},
				{"apply", sharedLabels[Lang::it]["apply"]},
				{"noError", sharedLabels[Lang::it]["noError"]},
				{"errInvalidPassword", sharedLabels[Lang::it]["errInvalidPassword"]},
				{"errPasswordsNotMatching", sharedLabels[Lang::it]["errPasswordsNotMatching"]},
			}
		},
	};

	void debug();
}

#endif // RESOURCES_H
