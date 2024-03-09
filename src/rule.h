#ifndef RULE_H
#define RULE_H

#include <QDateTime>
#include <QString>

struct Rule {
	enum When { before, after };
	int id;
	int entry_id;
	When when;
	QDateTime date;
	QString color = "";
	QString highlight = "";

	Rule(
			int id,
			int entry_id,
			When when,
			QDateTime date,
			QString color,
			QString highlight
		);
};

#endif
