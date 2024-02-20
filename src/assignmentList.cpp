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
#include <QSettings>

#include "assignmentList.h"
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

	this->setupDB();
	this->displayDate();
	this->displayWidgets();
	this->show();
}

void AssignmentList::setupDB() {
	qDebug() << "WIP";
}

void AssignmentList::displayDate() {
	QDate today = QDate::currentDate();
	ui.title->setText(today.toString("dddd, MMM d yyyy"));
}

void AssignmentList::displayWidgets() {
	//this->drawGroups();
}

// Open the 'addGroup' form
void AssignmentList::addGroup() {
	qDebug() << "WIP";
}

// Open the 'editGroup; form
void AssignmentList::editGroup(int id) {
	qDebug() << "WIP";
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
