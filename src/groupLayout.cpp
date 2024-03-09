#include <QLabel>
#include <QMenu>
#include <QString>

#include <QDebug>

#include "addEntryForm.h"
#include "editGroupForm.h"
#include "groupLayout.h"
#include "lib.h"

GroupLayout::GroupLayout(const Group &g) :
	group(g)
{
	this->setContentsMargins(0, 10, 0, 10);

	QLabel *name_label = new QLabel(this->group.name);
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

void GroupLayout::showContextMenu() {
	QMenu menu;

	QAction *add_entry_act = new QAction("Add Entry");
	QObject::connect(add_entry_act, &QAction::triggered, this, &GroupLayout::addEntry);
	menu.addAction(add_entry_act);

	QAction *edit_group_act = new QAction("Edit Group");
	QObject::connect(edit_group_act, &QAction::triggered, this, &GroupLayout::editGroup);
	menu.addAction(edit_group_act);

	QAction *del_group_act = new QAction("Remove Group");
	QObject::connect(del_group_act, &QAction::triggered, this, &GroupLayout::removeGroup);
	menu.addAction(del_group_act);

	menu.exec(QCursor::pos());
}

void GroupLayout::addEntry() {
	AddEntryForm create_new_entry_dialog(this->group);
	if(create_new_entry_dialog.exec() == QDialog::Accepted)
		getMainWindow()->displayWidgets();
}

void GroupLayout::editGroup() {
	EditGroupForm edit_group_dialog(this->group);
	if(edit_group_dialog.exec() == QDialog::Accepted)
		getMainWindow()->displayWidgets();
}

void GroupLayout::removeGroup() {
	qDebug() << "WIP";
}
