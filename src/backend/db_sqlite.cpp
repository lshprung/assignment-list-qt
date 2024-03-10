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
						Group::Column(query.record().field("column").value().toInt()),
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

		query.exec("SELECT * FROM entries");
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

QList<Entry *> BackendDB::loadEntries(int parent_id) {
	QList<Entry *> output;

	{
		QSqlDatabase database(this->openDB());
		QSqlQuery query;

		query.prepare("SELECT * FROM entries WHERE parent_id = ?");
		query.bindValue(0, parent_id);
		query.exec();
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

// insert group to the database (returns 0 if failed)
int BackendDB::insertEntry(const Entry &new_entry) {
	int output;

	{
		QSqlDatabase database(this->openDB());
		QSqlQuery query;

		query.prepare("INSERT INTO entries (parent_id, description, due_date, alt_due_date, link, color, highlight) VALUES (:p_id, :desc, :due, :alt_due, :link, :color, :highlight)");
		query.bindValue(":p_id", new_entry.parent_id);
		query.bindValue(":desc", new_entry.desc);
		query.bindValue(":due", new_entry.due.toString("yyyy-MM-dd"));
		query.bindValue(":alt_due", new_entry.due_alt);
		query.bindValue(":link", new_entry.link);
		query.bindValue(":color", new_entry.color);
		query.bindValue(":highlight", new_entry.highlight);
		query.exec();

		output = query.lastInsertId().toInt();
	}

	QSqlDatabase::removeDatabase("qt_sql_default_connection");
	return output;
}

void BackendDB::updateGroup(const Group &group) {
	{
		QSqlDatabase database(this->openDB());
		QSqlQuery query;

		query.prepare("UPDATE groups SET "
				"name = :name, "
				"column = :column, "
				"link = :link, "
				"hidden = :hidden "
				"WHERE id = :id");
		query.bindValue(":name", group.name);
		query.bindValue(":column", group.column);
		query.bindValue(":link", group.link);
		query.bindValue(":hidden", group.hidden);
		query.bindValue(":id", group.id);
		query.exec();
	}

	QSqlDatabase::removeDatabase("qt_sql_default_connection");
}

// hide group and entries belonging to group
// return value: number of affected rows
int BackendDB::removeGroup(const Group &group) {
	int output;

	{
		QSqlDatabase database(this->openDB());
		QSqlQuery query;

		// First, set entries to hidden
		query.prepare("UPDATE entries SET hidden = 1 WHERE parent_id = ?");
		query.bindValue(0, group.id);
		query.exec();

		// Now, set the group to hidden
		query.prepare("UPDATE groups SET hidden = 1 WHERE id = ?");
		query.bindValue(0, group.id);
		query.exec();

		// FIXME not sure if this also needs to be called after the first query...
		output = query.numRowsAffected();
	}

	QSqlDatabase::removeDatabase("qt_sql_default_connection");
	return output;
}

// permanently delete removed/hidden groups and entries
void BackendDB::cleanHidden() {
	{
		QSqlDatabase database(this->openDB());
		QSqlQuery query;

		// remove rules associated with hidden entries
		query.exec("DELETE FROM rules WHERE id IN ("
				"SELECT rules.id FROM rules"
				"INNER JOIN entries ON rules.entry_id = entries.id"
				"WHERE entries.hidden = 1)");
		// remove hidden entries
		query.exec("DELETE FROM entries WHERE hidden = 1");
		// remove hidden groups
		query.exec("DELETE FROM groups WHERE hidden = 1");
	}

	QSqlDatabase::removeDatabase("qt_sql_default_connection");
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
