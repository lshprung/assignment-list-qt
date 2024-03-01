#include <QLabel>
#include <QMenu>
#include <QString>

#include <QDebug>

#include "group.h"

Group::Group(int id, QString name, QString column, QString link, bool hidden) :
	id(id),
	name(name),
	column(column),
	link(link),
	hidden(hidden)
{
	this->setContentsMargins(0, 10, 0, 10);

	QLabel *name_label = new QLabel(this->name);
	name_label->setTextInteractionFlags(Qt::TextSelectableByMouse);
	name_label->setToolTip("Right-Click for actions");
	name_label->setContextMenuPolicy(Qt::CustomContextMenu);
	//name_label->customContextMenuRequested(const QPoint &pos)
	QObject::connect(name_label, 
			SIGNAL(customContextMenuRequested(const QPoint &)),
			SLOT(showContextMenu()));
	
	QFont name_font = QFont("Arial", 13);
	name_font.setUnderline(true);
	name_label->setFont(name_font);

	this->addWidget(name_label);
}

void Group::showContextMenu() {
	QMenu menu;

	QAction *add_entry_act = new QAction("Add Entry");
	QObject::connect(add_entry_act, &QAction::triggered, this, &Group::addEntry);
	menu.addAction(add_entry_act);

	QAction *edit_group_act = new QAction("Edit Group");
	QObject::connect(edit_group_act, &QAction::triggered, this, &Group::editGroup);
	menu.addAction(edit_group_act);

	QAction *del_group_act = new QAction("Remove Group");
	QObject::connect(del_group_act, &QAction::triggered, this, &Group::removeGroup);
	menu.addAction(del_group_act);

	menu.exec(QCursor::pos());
}

void Group::addEntry() {
	qDebug() << "WIP";
}

void Group::editGroup() {
	qDebug() << "WIP";
}

void Group::removeGroup() {
	qDebug() << "WIP";
}
