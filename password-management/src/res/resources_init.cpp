#include "resources.h"

namespace res {
	QIcon windowIcon;

	Config config{};
	const QFont iconFont {"Bitstream Charter", iconFontSize};
#if OS_MOBILE
	StyleSheet darkTheme{":/qdarkstyle/mobile.qss"};
#else
	StyleSheet darkTheme{":/qdarkstyle/desktop.qss"};
#endif

	const QHash<Lang, QHash<QString, QString>> sharedLabels {
		{
			Lang::en, {
				{"langName", "English"},
				{"toolName", "Password management"},
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
				{"toolName", "Gestione password"},
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
				{"defaultWindowTitle", sharedLabels[Lang::en]["toolName"]},
				{"windowTitle", "%1 - " + sharedLabels[Lang::en]["toolName"]},
				{"usernameDefault", ""},
				{"questionRemovalTitle", "Removing \"%1\"..."},
				{"questionRemoval", "Do you really want to remove password \"%1\"?"},
			}
		},
		{
			Lang::it, {
				{"defaultWindowTitle", sharedLabels[Lang::it]["toolName"]},
				{"windowTitle", "%1 - " + sharedLabels[Lang::it]["toolName"]},
				{"usernameDefault", ""},
				{"questionRemovalTitle", "Rimuovendo \"%1\"..."},
				{"questionRemoval", "Vuoi davvero rimuovere la password \"%1\"?"},
			}
		},
	};
	const QHash<Lang, QHash<QString, QString>> loginLabels {
		{
			Lang::en, {
				{"windowTitle", "Login - " + sharedLabels[Lang::en]["toolName"]},
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
				{"windowTitle", "Accesso - " + sharedLabels[Lang::it]["toolName"]},
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
				{"editWindowTitle", "Edit - " + sharedLabels[Lang::en]["toolName"]},
				{"newWindowTitle", "New - " + sharedLabels[Lang::en]["toolName"]},
				{"editPassword", "Edit password \"%1\""},
				{"newPassword", "New password"},
				{"ok", sharedLabels[Lang::en]["ok"]},
				{"cancel", sharedLabels[Lang::en]["cancel"]},
				{"nameTitle", sharedLabels[Lang::en]["nameTitle"] + ":"},
				{"passwordTitle", sharedLabels[Lang::en]["passwordTitle"] + ":"},
				{"emailTitle", sharedLabels[Lang::en]["emailTitle"] + ":"},
				{"usernameTitle", sharedLabels[Lang::en]["usernameTitle"] + ":"},
			}
		},
		{
			Lang::it, {
				{"editWindowTitle", "Modifica - " + sharedLabels[Lang::it]["toolName"]},
				{"newWindowTitle", "Nuova - " + sharedLabels[Lang::it]["toolName"]},
				{"editPassword", "Modifica password \"%1\""},
				{"newPassword", "Nuova password"},
				{"ok", sharedLabels[Lang::it]["ok"]},
				{"cancel", sharedLabels[Lang::it]["cancel"]},
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
				{"windowTitle", "Settings - " + sharedLabels[Lang::en]["toolName"]},
				{"languageTitle", "Language:"},
				{"reorderingTitle", "Password reordering"},
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
				{"passwordRequestWindowTitle", "Insert password"},
				{"passwordRequestTitle", sharedLabels[Lang::en]["passwordTitle"] + ":"},
				{"noError", sharedLabels[Lang::en]["noError"]},
				{"errInvalidPassword", sharedLabels[Lang::en]["errInvalidPassword"]},
				{"errPasswordsNotMatching", sharedLabels[Lang::en]["errPasswordsNotMatching"]},
			}
		},
		{
			Lang::it, {
				{"windowTitle", "Impostazioni - " + sharedLabels[Lang::it]["toolName"]},
				{"languageTitle", "Lingua:"},
				{"reorderingTitle", "Ordinazione password"},
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
				{"passwordRequestWindowTitle", "Inserisci password"},
				{"passwordRequestTitle", sharedLabels[Lang::it]["passwordTitle"] + ":"},
				{"noError", sharedLabels[Lang::it]["noError"]},
				{"errInvalidPassword", sharedLabels[Lang::it]["errInvalidPassword"]},
				{"errPasswordsNotMatching", sharedLabels[Lang::it]["errPasswordsNotMatching"]},
			}
		},
	};
	const QHash<Lang, QHash<QString, QString>> infoLabels {
		{
			Lang::en, {
				{"windowTitle", "Info - " + sharedLabels[Lang::en]["toolName"]},
				{"pwnedTitle", "Have I Been Pwned?"},
				{"pwnedLoading", ""},
				{"pwnedEmail", "\"%1\": seen in %2 breaches"},
				{"pwnedPassword", "\"%1\": seen %2 times before"},
				{"helpTitle", "Help"},
				{"helpText", "<html><head/><body><p>TO<br/>DO</p></body></html>"},
				{"infoTitle", "Info"},
				{"infoText", "<html><head/><body><p>TO<br/>DO</p></body></html>"},
			}
		},
		{
			Lang::it, {
				{"windowTitle", "Informazioni - " + sharedLabels[Lang::it]["toolName"]},
				{"pwnedTitle", "Have I Been Pwned?"},
				{"pwnedLoading", ""},
				{"pwnedEmail", "\"%1\": compare in %2 brecce"},
				{"pwnedPassword", "\"%1\": già vista %2 volte"},
				{"helpTitle", "Aiuto"},
				{"helpText", "<html><head/><body><p>DA<br/>FARE</p></body></html>"},
				{"infoTitle", "Informazioni"},
				{"infoText", "<html><head/><body><p>DA<br/>FARE</p></body></html>"},
			}
		},
	};
}
