#ifndef BACKEND_DB_SQLITE_H
#define BACKEND_DB_SQLITE_H

#include <QString>
#include <QStringList>
#include <qsqldatabase.h>

#include "../entry.h"
#include "../group.h"
#include "../rule.h"

class BackendDB : QSqlDatabase {
	public:
		BackendDB();
		QList<Group> loadGroups();
		QList<Entry> loadEntries();
		QList<Entry> loadEntries(int parent_id);
		QList<Rule> loadRules();
		QList<Rule> loadRules(int entry_id);
		int insertGroup(const Group &new_group);
		int insertEntry(const Entry &new_entry);
		int insertRule(const Rule &new_rule);
		void updateGroup(const Group &group);
		void updateEntry(const Entry &entry);
		void updateRule(const Rule &rule);
		int removeGroup(const Group &group);
		int removeEntry(const Entry &entry);
		int removeRule(const Rule &rule);
		void cleanHidden();

	private:
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
				"before_after INTEGER,"
				"date TEXT NOT NULL,"
				"color VARCHAR(255) DEFAULT NULL,"
				"highlight VARCHAR(255) DEFAULT NULL"
				")"
		};

		QString getDBPath();
		QSqlDatabase openDB();
};

#endif
