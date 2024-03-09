#ifndef GROUP_H
#define GROUP_H

#include <QString>

struct Group {
	int id;
	QString name;
	QString column;
	QString link;
	bool hidden;

	Group(
			int id, 
			QString name, 
			QString column = "left", 
			QString link = "", 
			bool hidden = false
		 );
};

#endif
