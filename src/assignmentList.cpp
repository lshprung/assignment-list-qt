#include <QAction>
#include <QApplication>
#include <QCoreApplication>
#include <QDate>
#include <QFile>
#include <QMessageBox>
#include <QObject>
#include <QStandardPaths>
#include <QUiLoader>

#include <QDebug>
#include <QErrorMessage>
#include <QSettings>

#include "add_group_form.h"
#include "assignmentList.h"
#include "backend/db_sqlite.h"
#include "settings.h"

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
	QFile path = settings.fileName();

	if(!path.exists()) {
		qDebug() << "Creating Config";
		Settings::createConfig();
	}
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
	QList<Group *> groups = database.loadGroups();
	int i;

	// clear out old layouts if they exist
	this->recursiveClear(ui.groups_layout);

	for(i = 0; i < groups.size(); ++i) {
		if(groups[i]->hidden) continue;
		// TODO set right click behavior
		// TODO add entries to this layout
		if(groups[i]->column.toLower() == "left") column_left->addLayout(groups[i]);
		else column_right->addLayout(groups[i]);
	}

	column_left->addStretch();
	column_right->addStretch();

	ui.groups_layout->addLayout(column_left, 0, 0);
	ui.groups_layout->addLayout(column_right, 0, 1);
}

// Open the 'addGroup' form
void AssignmentList::addGroup() {
	AddGroupForm create_new_group_dialog;
	if(create_new_group_dialog.exec() == QDialog::Accepted)
		this->displayWidgets();
}

void AssignmentList::preferences() {
	qDebug() << "WIP";
}

void AssignmentList::reload() {
	qDebug() << "WIP";
}

void AssignmentList::cleanHidden() {
	qDebug() << "WIP";
}

void AssignmentList::aboutDialog() {
	QMessageBox about;
	about.about(this, "About Assignment List", "Created by Louie S. - 2023");
}

void AssignmentList::recursiveClear(QLayout *layout) {
	QLayoutItem *child;
	while((child = layout->takeAt(0)) != nullptr) {
		if(child->layout()) this->recursiveClear(child->layout());
		delete child->widget();
		delete child;
	}
}
