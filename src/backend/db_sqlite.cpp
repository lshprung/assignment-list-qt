#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include <QSqlError>

#include "db_sqlite.h"

QString BackendDB::getDBPath() {
	QSettings settings;
	settings.beginGroup("paths");
	return settings.value("db_path").toString();
}

void BackendDB::init() {
	QString db_path(BackendDB::getDBPath());
	int i;

	// Check if database already exists
	if(QFile::exists(db_path))
		return;

	// Check if directory exists
	if(!QFileInfo(db_path).dir().exists()) {
		if(!QFileInfo(db_path).dir().mkpath(QFileInfo(db_path).dir().absolutePath())) {
			qDebug() << "Error creating db file";
			std::exit(1);
		}
	}

	// Create database
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName(db_path);

	// TODO see if explicitly creating the parent directory is necessary
	database.open();
	if(database.isOpenError()) {
		// FIXME end-user friendly error message
		qDebug() << database.lastError();
		std::exit(1);
	}

	QSqlQuery query;

	// Erase database contents so that we don't have duplicates
	query.exec("DROP TABLE groups");
	query.exec("DROP TABLE entries");
	query.exec("DROP TABLE rules");

	for(i = 0; i < BackendDB::create_table_queries.length(); ++i)
		query.exec(BackendDB::create_table_queries[i]);

	qDebug() << database.lastError();

	database.close();
}
