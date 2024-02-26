#ifndef RULE_H
#define RULE_H

#include <QDateTime>
#include <QHBoxLayout>
#include <QString>

// rule's widgets will always be allocated, even though they are only rendered when options are open
// TODO determine whether an alternative approach is better (same goes for group and entry)

class Rule : QHBoxLayout {
	public:
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
