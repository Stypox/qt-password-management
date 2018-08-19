#include "resources.h"
#include <QRegExp>
#include <QApplication>
#include <QDebug>

namespace res {
	Config::Config() : m_filename{"password-management.conf"},
		m_directory{
		#if OS_MOBILE
			static_cast<QString>(getenv("EXTERNAL_STORAGE") ? getenv("EXTERNAL_STORAGE") : QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation))
		#elif defined(Q_OS_LINUX)
			QStandardPaths::writableLocation(QStandardPaths::StandardLocation::HomeLocation)
		#else
			QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation)
		#endif
			+ "/.password-management/"} {
		QDir().mkdir(m_directory);

		QFile configFile {m_directory + m_filename};
		configFile.open(QIODevice::ReadOnly);

		QByteArray line = configFile.readLine();
		if (!line.isEmpty() && line.back() == '\n')
			line.chop(1);
		if (!line.isEmpty() && line.back() == '\r')
			line.chop(1);
		bool langOk;
		int language = line.toInt(&langOk);
		if (langOk && language >= static_cast<int>(Lang::min) && language <= static_cast<int>(Lang::max))
			m_language = static_cast<Lang>(language);
		else
			m_language = Lang::def;

		line = configFile.readLine();
		if (!line.isEmpty() && line.back() == '\n')
			line.chop(1);
		if (!line.isEmpty() && line.back() == '\r')
			line.chop(1);
		m_defaultUsername = line;
	}
	Config::~Config() {
		save();
	}
	void Config::save() const {
		QFile configFile {m_directory + m_filename};
		configFile.open(QIODevice::WriteOnly);

		configFile.write((QString::number(static_cast<int>(m_language)) + "\n" + m_defaultUsername).toUtf8());
	}

	const QString& Config::dataDir() const {
		return m_directory;
	}
	const Lang& Config::language() const {
		return m_language;
	}
	const QString& Config::username() const {
		return m_defaultUsername;
	}

	void Config::setLanguage(const Lang& language) {
		m_language = language;
		save();
	}
	void Config::setUsername(const QString& defaultUsername) {
		m_defaultUsername = defaultUsername;
		save();
	}

	bool isEmailValid(QString email) {
		static QRegExp emailValidator("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b", Qt::CaseInsensitive, QRegExp::RegExp);
		return emailValidator.exactMatch(email);
	}

	void debug() {
		qDebug() << "Resources:";
		qDebug() << "Mobile:   " << OS_MOBILE;
		qDebug() << "Data path:" << config.dataDir();
		qDebug() << "Language: " << sharedLabels[config.language()]["langName"];
		qDebug() << "DarkStyleSheet: " << (darkTheme.data().size() < 10 ? darkTheme : darkTheme.data().mid(0, 10) + "...");
	}

	StyleSheet::StyleSheet(const QString& filename) : m_filename{filename}, m_data{""} {}

	void StyleSheet::load()	{
		QFile styleSheetFile (m_filename);
		if (styleSheetFile.exists()) {
			styleSheetFile.open(QFile::ReadOnly | QFile::Text);
			m_data = QString::fromUtf8(styleSheetFile.readAll());
		}
		else {
			qDebug() << "Error loading style sheet " << m_filename << ": file doesn't exists";
			m_data = "";
		}
	}

	QString StyleSheet::data() const {
		return m_data;
	}
	StyleSheet::operator QString() const {
		return m_data;
	}

}
