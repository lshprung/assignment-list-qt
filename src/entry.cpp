#include <QList>

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

QList<Entry> Entry::entries;

bool Entry::compare(Entry a, Entry b) {
	// 1st level: sort not done before done
	if(a.done != b.done)
		return a.done < b.done;
	// next level: sort on due date
	if(a.due != b.due)
		return a.due < b.due;
	// next level: sort on alt due date
	if(a.due_alt != b.due_alt)
		return a.due_alt < b.due_alt;
	// next level: sort on description
	if(a.desc != b.desc)
		return a.desc < b.desc;
	// otherwise, sort on id
	return a.id < b.id;
}
