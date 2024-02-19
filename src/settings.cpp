#include <QDir>
#include <QSettings>
#include <QStandardPaths>

#include "settings.h"

void Settings::createConfig() {
	QSettings settings;
	QDir local_data_dir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));

	settings.beginGroup("paths");
	settings.setValue("db_path", local_data_dir.filePath("data.db"));
	settings.endGroup();
}
