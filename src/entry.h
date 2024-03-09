#ifndef ENTRY_H
#define ENTRY_H

#include <QDateTime>
#include <QString>
#include <QUrl>

struct Entry {
	int id;
	int parent_id;
	QString desc;
	QDateTime due;
	QString due_alt;
	QUrl link;
	QString color; // consider making this a QColor instead
	QString highlight; // see color comment
	bool done;
	bool hidden;

	Entry(
			int id,
			int parent_id,
			QString desc,
			QDateTime due = QDateTime(),
			QString due_alt = "",
			QUrl link = QUrl(),
			QString color = "",
			QString highlight = "",
			bool done = false,
			bool hidden = false
		 );
};

#endif
