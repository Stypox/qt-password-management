#ifndef RESOURCES_H
#define RESOURCES_H
#include <QFont>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QString>
#include <QIcon>
#include <memory>

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
#define OS_MOBILE true
#else
#define OS_MOBILE false
#endif


namespace res {
	extern QIcon windowIcon;


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
		const QString& username() const;

		void setLanguage(const Lang& language);
		void setUsername(const QString& defaultUsername);
	private:
		void save() const;

		const QString m_filename;

		const QString m_directory;
		Lang m_language;
		QString m_defaultUsername;
	};
	extern Config config;


	constexpr const char * dataFileExt = ".txt";
	constexpr const char * backupFileExt = ".bak";


	constexpr int iconFontSize {(OS_MOBILE ? 35 : 15)};
	extern const QFont iconFont;
	constexpr int passwordWidgetClosedHeight {(OS_MOBILE ? 150 : 45)};
	constexpr int passwordWidgetOpenedHeight {(OS_MOBILE ? 400 : 140)};


	class StyleSheet {
	public:
		explicit StyleSheet(const QString& filename);

		void load();

		QString data() const;
		operator QString() const;
	private:
		const QString m_filename;
		QString m_data;
	};
	extern StyleSheet darkTheme;


	bool isEmailValid(QString email);


	//s stands for "settings" and p for "password"
	namespace json {
		constexpr const char * basicStructure {R"json({"settings": {}, "passwords": []})json"};
		constexpr const char * settingsStructure {R"json({"language": %1, "reorderingActive": %2, "darkThemeActive": %3, "removalConfirmationDialogActive": %4, "pwnedActive": %5})json"};
		constexpr const char * passwordStructure {R"json({"name": "%1", "password": "%2", "email": "%3", "username": "%4", "description": "%5"})json"};
		constexpr const char * settings {"settings"};
		constexpr const char * sLanguage {"language"};
		constexpr const char * sReorderingActive {"reorderingActive"};
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


	extern const QHash<Lang, QHash<QString, QString>> sharedLabels;
	extern const QHash<Lang, QHash<QString, QString>> passwordsLabels;
	extern const QHash<Lang, QHash<QString, QString>> loginLabels;
	extern const QHash<Lang, QHash<QString, QString>> addEditLabels;
	extern const QHash<Lang, QHash<QString, QString>> widgetLabels;
	extern const QHash<Lang, QHash<QString, QString>> settingsLabels;
	extern const QHash<Lang, QHash<QString, QString>> infoLabels;


	void debug();
}

#endif // RESOURCES_H
