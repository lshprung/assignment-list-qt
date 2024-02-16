#ifndef ASSIGNMENTLIST_H
#define ASSIGNMENTLIST_H

#include <QMainWindow>
#include "ui_main.h"

class AssignmentList : public QMainWindow {
	Q_OBJECT

	public:
		AssignmentList();

	private:
		Ui::MainWindow ui;

		void initializeUI();
		void createMenu();
		void createToolbar();
		void setupDB();
		void displayWidgets();
		void editGroup(int id);
		void removeGroup(int id);
		void groupContextMenu(int group_id);
		void addEntry(int parent); // TODO figure out type for parameter
		void editEntry(int id);
		void toggleDoneEntry(int id);
		void removeEntry(int id);
		void editRules(int id);
		void entryContextMenu(int entry_id);
		void drawGroups();
		void drawEntries();

	private slots:
		void preferences();
		void reload();
		void addGroup();
		void cleanHidden();
		void aboutDialog();
};

#endif
