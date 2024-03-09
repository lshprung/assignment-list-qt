#include "entry.h"

Entry::Entry(int id, int parent_id, QString desc, QDateTime due, QString due_alt, QUrl link, QString color, QString highlight, bool done, bool hidden) :
	id(id),
	parent_id(parent_id),
	desc(desc),
	due(due),
	due_alt(due_alt),
	link(link),
	color(color),
	highlight(highlight),
	done(done),
	hidden(hidden) 
{
}
