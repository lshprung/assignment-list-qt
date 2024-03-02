#ifndef ASSIGNMENTLIST_H
#define ASSIGNMENTLIST_H

#include <QMainWindow>
#include <QSettings>
#include <QVBoxLayout>

#include "ui_assignmentList.h"

class AssignmentList : public QMainWindow {
	Q_OBJECT

	public:
		QSettings configuration;

		AssignmentList();
		void displayWidgets();

	private:
		Ui::MainWindow ui;

		void initializeSettings();
		void initializeUI();
		void displayDate();
		QVBoxLayout *drawEntries(int parent_id);
		void editEntry(int id);
		void toggleDoneEntry(int id);
		void removeEntry(int id);
		void editRules(int id);
		void entryContextMenu(int entry_id);
		void drawGroups();
		void drawEntries();

		// helpers
		// used to clear out the grid layout when a refresh occurs
		void recursiveClear(QLayout *layout);

	private slots:
		void preferences();
		void reload();
		void addGroup();
		void cleanHidden();
		void aboutDialog();
};

#endif
