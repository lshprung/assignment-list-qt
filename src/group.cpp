#include <QLabel>
#include <QString>

#include "group.h"

Group::Group(int id, QString name, QString column, QString link, bool hidden) {
	this->id = id;
	this->name = name;
	this->column = column;
	this->link = link;
	this->hidden = hidden;

	this->setContentsMargins(0, 10, 0, 10);

	QLabel *name_label = new QLabel(this->name);
	name_label->setTextInteractionFlags(Qt::TextSelectableByMouse);
	
	QFont name_font = QFont("Arial", 13);
	name_font.setUnderline(true);

	name_label->setFont(name_font);
	this->addWidget(name_label);
}
