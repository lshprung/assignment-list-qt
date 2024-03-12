#include <QLabel>
#include <QMenu>

#include <QDebug>

#include "backend/db_sqlite.h"
#include "editEntryForm.h"
#include "entryLayout.h"
#include "lib.h"

EntryLayout::EntryLayout(const Entry &e) :
	entry(e)
{
	QLabel *bullet = new QLabel();
	QLabel *body = new QLabel();

	// set styling
	this->setContentsMargins(2, 2, 2, 2);

	bullet->setFont(QFont("Arial", 11));
	bullet->setMaximumWidth(15);

	body->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse);
	body->setFont(QFont("Arial", 11));
	body->setWordWrap(true);
	body->setToolTip("Right-Click for actions");
	body->setContextMenuPolicy(Qt::CustomContextMenu);

	// set context menu
	body->setContextMenuPolicy(Qt::CustomContextMenu);
	QObject::connect(body,
			SIGNAL(customContextMenuRequested(const QPoint &)),
			SLOT(showContextMenu()));

	// Check rules
	// TODO

	// set conditional styling
	if(this->entry.done) {
		bullet->setText("\u2713");
		/*
		bullet->setStyleSheet(
				"QLabel {"
				"	color: green;"
				"}"
				);
		*/
	}
	else
		bullet->setText("- ");
	this->addWidget(bullet);

	if(!this->entry.due.isNull())
		body->setText(this->entry.due.toString("MM/dd/yyyy: "));
	else if(!this->entry.due_alt.isEmpty())
		body->setText(this->entry.due_alt + ": ");

	if(!this->entry.link.isEmpty()) {
		body->setOpenExternalLinks(true);
		body->setText(body->text() + "<a href=\"" + this->entry.link.toString() + "\" " "style=\"color: " + (this->entry.color.isEmpty() ? "default" : this->entry.color ) + ";\">");
	}
	body->setText(body->text() + this->entry.desc);
	if(!this->entry.link.isEmpty()) {
		body->setText(body->text() + "</a>");
		body->setToolTip(this->entry.link.toString());
	}

	if(this->entry.done) {
		QFont body_font = body->font();
		body_font.setStrikeOut(true);
		body->setFont(body_font);
		/*
		body->setStyleSheet(
				"QLabel {"
				"	color: green"
				"}"
				);
		*/
	}
	else {
		/*
		body->setStyleSheet(
				"QLabel {"
				"	color: " + (this->color.isEmpty() ? "default" : this->color) + ";"
				"	background-color: " + (this->highlight.isEmpty() ? "none" : this->highlight) + ";"
				"	font-weight: " + (this->due.isValid() && this->due <= QDateTime::currentDateTime() ? "bold" : "normal") + ";"
				";"
				);
		*/
	}

	this->addWidget(body);
}

void EntryLayout::showContextMenu() {
	QMenu menu;

	QAction *edit_entry_act = new QAction("Edit Entry");
	QObject::connect(edit_entry_act, &QAction::triggered, this, &EntryLayout::editEntry);
	menu.addAction(edit_entry_act);

	QAction *set_rules_act = new QAction("Rules");
	QObject::connect(edit_entry_act, &QAction::triggered, this, &EntryLayout::setRules);
	menu.addAction(set_rules_act);

	QAction *toggle_done_act = new QAction("Done");
	toggle_done_act->setCheckable(true);
	if(this->entry.done) toggle_done_act->setChecked(true);
	QObject::connect(toggle_done_act, &QAction::triggered, this, &EntryLayout::toggleDone);
	menu.addAction(toggle_done_act);

	QAction *del_entry_act = new QAction("Remove Entry");
	QObject::connect(del_entry_act, &QAction::triggered, this, &EntryLayout::removeEntry);
	menu.addAction(del_entry_act);

	menu.exec(QCursor::pos());
}

void EntryLayout::editEntry() {
	EditEntryForm edit_entry_dialog(this->entry);
	if(edit_entry_dialog.exec() == QDialog::Accepted)
		getMainWindow()->displayWidgets();
}

void EntryLayout::setRules() {
	qDebug() << "WIP";
}

void EntryLayout::toggleDone() {
	BackendDB database;

	this->entry.done = !this->entry.done;
	database.updateEntry(this->entry);
	getMainWindow()->displayWidgets();
}

void EntryLayout::removeEntry() {
	BackendDB database;

	if(database.removeEntry(this->entry) > 0)
		getMainWindow()->displayWidgets();
}
