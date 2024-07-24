#include <QList>

#include "group.h"

Group::Group(int id, QString name, Group::Column column, QString link, bool hidden) :
	id(id),
	name(name),
	column(column),
	link(link),
	hidden(hidden)
{
}

QList<Group> Group::groups;
