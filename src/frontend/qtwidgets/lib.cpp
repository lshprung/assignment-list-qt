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

void recursiveClear(QLayout *layout) {
	QLayoutItem *child;
	while((child = layout->takeAt(0)) != nullptr) {
		if(child->layout()) recursiveClear(child->layout());
		delete child->widget();
		delete child;
	}
}
