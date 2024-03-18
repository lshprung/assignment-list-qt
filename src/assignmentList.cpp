#include <algorithm>
#include <QAction>
#include <QApplication>
#include <QCoreApplication>
#include <QDate>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QObject>
#include <QSettings>
#include <QStandardPaths>
#include <QUiLoader>

#include <QDebug>
#include <QErrorMessage>

#include "../config.h"
#include "addGroupForm.h"
#include "assignmentList.h"
#include "backend/db_sqlite.h"
#include "entryLayout.h"
#include "groupLayout.h"
#include "lib.h"
#include "preferencesDialog.h"

AssignmentList::AssignmentList() {
	// set QSettings information
	QCoreApplication::setOrganizationName("assignment-list-qt"); // TODO grab this from a config.h type file
	QCoreApplication::setApplicationName("assignment-list-qt"); // TODO grab this from a config.h type file

	// ensure QSettings location exists
	this->initializeSettings();

	// load uic
	ui.setupUi(this);
	this->initializeUI();
}

void AssignmentList::initializeSettings() {
	QSettings settings;
	QDir local_data_dir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));

	settings.beginGroup("paths");
	if(!settings.contains("db_path")) {
		qDebug() << "Setting default db_path";
		settings.setValue("db_path", local_data_dir.filePath("data.db"));
	}
	settings.endGroup();
}

void AssignmentList::initializeUI() {
	// create menu connections
	QObject::connect(ui.actionPreferences, &QAction::triggered, this, &AssignmentList::preferences);
	QObject::connect(ui.actionReload, &QAction::triggered, this, &AssignmentList::reload);
	QObject::connect(ui.actionExit, &QAction::triggered, this, QApplication::quit);
	QObject::connect(ui.actionAdd_Group, &QAction::triggered, this, &AssignmentList::addGroup);
	QObject::connect(ui.actionClean_Hidden, &QAction::triggered, this, &AssignmentList::cleanHidden);
	QObject::connect(ui.actionAbout, &QAction::triggered, this, &AssignmentList::aboutDialog);

	// create toolbar
	ui.toolBar->addAction(ui.actionAdd_Group);

	this->displayDate();
	this->displayWidgets();
	this->show();
}

void AssignmentList::displayDate() {
	QDate today = QDate::currentDate();
	ui.title->setText(today.toString("dddd, MMM d yyyy"));
}

void AssignmentList::displayWidgets() {
	QVBoxLayout *column_left = new QVBoxLayout();
	QVBoxLayout *column_right = new QVBoxLayout();
	BackendDB database;
	QList<Group> groups = database.loadGroups();
	GroupLayout *new_group_layout;
	int i;

	// clear out old layouts if they exist
	recursiveClear(ui.groups_layout);

	for(i = 0; i < groups.size(); ++i) {
		if(groups[i].hidden) continue;
		new_group_layout = new GroupLayout(groups[i]);
		new_group_layout->addLayout(this->drawEntries(groups[i].id)); // add entries to layout
		if(groups[i].column == Group::left) column_left->addLayout(new_group_layout);
		else column_right->addLayout(new_group_layout);
	}

	column_left->addStretch();
	column_right->addStretch();

	ui.groups_layout->addLayout(column_left, 0, 0);
	ui.groups_layout->addLayout(column_right, 0, 1);
}

QVBoxLayout *AssignmentList::drawEntries(int parent_id) {
	BackendDB database;
	QList<Entry> entries = database.loadEntries(parent_id);
	QVBoxLayout *output = new QVBoxLayout;
	int i;

	// styling
	output->setContentsMargins(5, 0, 0, 0);

	// sort entries
	std::sort(entries.begin(), entries.end(), Entry::compare);

	for(i = 0; i < entries.size(); ++i) {
		// skip if this entry is set to hidden
		if(entries[i].hidden) continue;
		output->addLayout(new EntryLayout(entries[i]));
	}

	return output;
}

// Open the 'addGroup' form
void AssignmentList::addGroup() {
	AddGroupForm create_new_group_dialog;
	if(create_new_group_dialog.exec() == QDialog::Accepted)
		this->displayWidgets();
}

void AssignmentList::preferences() {
	PreferencesDialog preferences_dialog;
	if(preferences_dialog.exec() == QDialog::Accepted)
		this->displayWidgets();
}

void AssignmentList::reload() {
	this->displayWidgets();
}

void AssignmentList::cleanHidden() {
	QMessageBox::StandardButton are_you_sure;
	BackendDB database;

	// create 'are you sure?' dialog before going forward
	are_you_sure = QMessageBox::question(this, "Are You Sure?", 
			"Are you sure? All removed groups and entries will be permanently deleted from the database.",
			QMessageBox::Yes|QMessageBox::No);

	if(are_you_sure == QMessageBox::Yes)
		database.cleanHidden();
}

void AssignmentList::aboutDialog() {
	QMessageBox about;
	QString title("About " + QString(PROJECT_TITLE));
	QString text(
			QString(PROJECT_TITLE) + " " + QString(VERSION) + "\n" + 
			"Created by Louie S. - 2024");
	about.about(this, title, text);
}
