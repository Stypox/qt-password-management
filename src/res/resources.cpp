#include "resources.h"
#include <QDebug>

namespace res {
	Config::Config() : m_filename{"password-management.conf"},
		m_directory{QStandardPaths::writableLocation(QStandardPaths::StandardLocation::ConfigLocation) + "/"} {
		QFile configFile {m_directory + m_filename};
		configFile.open(QIODevice::ReadOnly);

		QString line = configFile.readLine();
		if (!line.isEmpty() && line.back() == '\n')
			line.chop(1);
		if (!line.isEmpty() && line.back() == '\r')
			line.chop(1);
		if (line.isEmpty()) {
			m_dataPath =
			#if OS_MOBILE
				static_cast<QString>(getenv("EXTERNAL_STORAGE") ? getenv("EXTERNAL_STORAGE") : QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation))
			#elif defined(Q_OS_LINUX)
				QStandardPaths::writableLocation(QStandardPaths::StandardLocation::HomeLocation)
			#else
				QStandardPaths::writableLocation(QStandardPaths::StandardLocation::AppDataLocation)
			#endif
				+ "/.password-management/";
		}
		else {
			m_dataPath = line;
		}

		line = configFile.readLine();
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
	}
	Config::~Config() {
		save();
	}
	void Config::save() const {
		QDir().mkdir(m_directory);
		QFile configFile {m_directory + m_filename};
		configFile.open(QIODevice::WriteOnly);

		configFile.write(m_dataPath.toUtf8());
		configFile.write("\n");
		configFile.write(QString::number(static_cast<int>(m_language)).toUtf8());
	}
	const QString& Config::dataPath() const {
		return m_dataPath;
	}
	const Lang& Config::language() const {
		return m_language;
	}

	void debug() {
		qDebug() << "Resources:";
		qDebug() << "Mobile:   " << (OS_MOBILE ? "True" : "False");
		qDebug() << "Data path:" << config.dataPath();
		qDebug() << "Language: " << sharedLabels[config.language()]["langName"];
	}
}
