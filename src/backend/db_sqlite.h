#ifndef BACKEND_DB_SQLITE_H
#define BACKEND_DB_SQLITE_H

#include <QString>
#include <QStringList>

namespace BackendDB {
	const QStringList create_table_queries = {
		"CREATE TABLE groups ("
			"id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
			"name VARCHAR(255) NOT NULL,"
			"column TINYINT(1) DEFAULT FALSE,"
			"link VARCHAR(255) NOT NULL,"
			"hidden TINYINT(1) DEFAULT FALSE"
			")",
		"CREATE TABLE entries ("
			"id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
			"parent_id REFERENCES groups (id),"
			"description VARCHAR(255) NOT NULL,"
			"due_date TEXT DEFAULT NULL,"
			"alt_due_date VARCHAR(255) DEFAULT NULL,"
			"link VARCHAR(255) DEFAULT NULL,"
			"color VARCHAR(255) DEFAULT NULL,"
			"highlight VARCHAR(255) DEFAULT NULL,"
			"done TINYINT(1) DEFAULT FALSE,"
			"hidden TINYINT(1) DEFAULT FALSE"
			")",
		"CREATE TABLE rules ("
			"id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL,"
			"entry_id REFERENCES entries (id),"
			"before_after TINYINT(1) DEFAULT TRUE,"
			"date TEXT NOT NULL,"
			"color VARCHAR(255) DEFAULT NULL,"
			"highlight VARCHAR(255) DEFAULT NULL"
			")"
	};

	QString getDBPath();
	void init();
	void load();
	void insertGroup(int new_group); // param datatype TBD
	void insertEntry(int new_entry); // param datatype TBD
	void insertRule(int new_rule); // param datatype TBD
	void updateGroup(int group); // param datatype TBD
	void updateEntry(int entry); // param datatype TBD
	void updateRule(int rule); // param datatype TBD
	void removeGroup(int group); // param datatype TBD
	void removeEntry(int entry); // param datatype TBD
	void removeRule(int rule); // param datatype TBD
	void cleanHidden();
};

#endif
