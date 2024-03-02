#include <QApplication>
#include <QMainWindow>
#include <QWidget>

#include "lib.h"

// shamelessly ripped from https://stackoverflow.com/a/46456214
AssignmentList *getMainWindow() {
	foreach(QWidget *w, QApplication::topLevelWidgets())
		if(AssignmentList *mainWin = qobject_cast<AssignmentList*>(w))
			return mainWin;
	return nullptr;
}
