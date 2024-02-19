#include <QAction>
#include <QApplication>
#include <QDate>
#include <QFile>
#include <QMessageBox>
#include <QObject>
#include <QUiLoader>

#include <QDebug>

#include "assignmentList.h"

AssignmentList::AssignmentList() {
	// load uic
	QFile file("/home/louie/Development/projects/assignment-list-qt/src/main.ui");
	file.open(QIODevice::ReadOnly);
	QUiLoader loader;
	ui.setupUi(this);

	this->initializeUI();
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

	//Config() // from config.h
	this->setupDB();
	this->displayWidgets();
	this->show();
}

void AssignmentList::setupDB() {
	qDebug() << "WIP";
}

void AssignmentList::displayWidgets() {
	QDate today = QDate::currentDate();
	ui.title->setText(today.toString("dddd, MMM d yyyy"));
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
