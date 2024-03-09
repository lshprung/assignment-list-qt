#include "group.h"

Group::Group(int id, QString name, QString column, QString link, bool hidden) :
	id(id),
	name(name),
	column(column),
	link(link),
	hidden(hidden)
{
}
