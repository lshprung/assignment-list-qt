#include <QList>

#include "rule.h"

Rule::Rule(int id, int entry_id, When when, QDateTime date, QString color, QString highlight) :
	id(id),
	entry_id(entry_id),
	when(when),
	date(date),
	color(color),
	highlight(highlight)
{
}

QList<Rule> Rule::rules;
