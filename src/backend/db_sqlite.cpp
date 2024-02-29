#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlField>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QSqlError>

#include "db_sqlite.h"

BackendDB::BackendDB() {
	QString db_path(getDBPath());
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
	{
		QSqlDatabase database(this->openDB());
		QSqlQuery query;

		// Erase database contents so that we don't have duplicates
		query.exec("DROP TABLE groups");
		query.exec("DROP TABLE entries");
		query.exec("DROP TABLE rules");

		for(i = 0; i < BackendDB::create_table_queries.length(); ++i)
			query.exec(BackendDB::create_table_queries[i]);
	}

	QSqlDatabase::removeDatabase("qt_sql_default_connection");
}

// load groups
QList<Group *> BackendDB::loadGroups() {
	QList<Group *> output;

	{
		QSqlDatabase database(this->openDB());
		QSqlQuery query;

		query.exec("SELECT * FROM groups");
		while(query.next()) {
			output.append(new Group(
						query.record().field("id").value().toInt(),
						query.record().field("name").value().toString(),
						query.record().field("column").value().toString(),
						query.record().field("link").value().toString(),
						query.record().field("hidden").value().toBool()));
		}
	}

	QSqlDatabase::removeDatabase("qt_sql_default_connection");
	return output;
}

// load entries
QList<Entry *> BackendDB::loadEntries() {
	QList<Entry *> output;

	{
		QSqlDatabase database(this->openDB());
		QSqlQuery query;

		query.exec("SELECT * FROM groups");
		while(query.next()) {
			output.append(new Entry(
						query.record().field("id").value().toInt(),
						query.record().field("parent_id").value().toInt(),
						query.record().field("description").value().toString(),
						query.record().field("due_date").value().toDateTime(),
						query.record().field("alt_due_date").value().toString(),
						query.record().field("link").value().toUrl(),
						query.record().field("color").value().toString(),
						query.record().field("highlight").value().toString(),
						query.record().field("done").value().toBool(),
						query.record().field("hidden").value().toBool()));
		}
	}

	QSqlDatabase::removeDatabase("qt_sql_default_connection");
	return output;
}

// load entries
QList<Rule *> BackendDB::loadRules() {
	QList<Rule *> output;

	{
		QSqlDatabase database(this->openDB());
		QSqlQuery query;

		query.exec("SELECT * FROM groups");
		while(query.next()) {
			output.append(new Rule(
						query.record().field("id").value().toInt(),
						query.record().field("entry_id").value().toInt(),
						(Rule::When) query.record().field("before_after").value().toInt(),
						query.record().field("date").value().toDateTime(),
						query.record().field("color").value().toString(),
						query.record().field("highlight").value().toString()));
		}
	}

	QSqlDatabase::removeDatabase("qt_sql_default_connection");
	return output;
}

// insert group to the database (returns 0 if failed)
int BackendDB::insertGroup(const Group &new_group) {
	int output;

	{
		QSqlDatabase database(this->openDB());
		QSqlQuery query;

		query.prepare("INSERT INTO groups (name, column, link) VALUES (?, ?, ?)");
		query.bindValue(0, new_group.name);
		query.bindValue(1, new_group.column);
		query.bindValue(2, new_group.link);
		query.exec();

		output = query.lastInsertId().toInt();
	}

	QSqlDatabase::removeDatabase("qt_sql_default_connection");
	return output;
}

QString BackendDB::getDBPath() {
	QSettings settings;
	settings.beginGroup("paths");
	return settings.value("db_path").toString();
}

QSqlDatabase BackendDB::openDB() {
	QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName(getDBPath());

	database.open();
	if(database.isOpenError()) {
		// FIXME end-user friendly error message
		qDebug() << database.lastError();
		std::exit(1);
	}

	return database;
}
