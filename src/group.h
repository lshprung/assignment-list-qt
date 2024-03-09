#ifndef GROUP_H
#define GROUP_H

#include <QString>

struct Group {
	enum Column { left, right };
	int id;
	QString name;
	Column column;
	QString link;
	bool hidden;

	Group(
			int id, 
			QString name, 
			Column column = left,
			QString link = "", 
			bool hidden = false
		 );
};

#endif
