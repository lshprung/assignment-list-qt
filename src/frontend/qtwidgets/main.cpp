#include <QApplication>
#include <QPushButton>

#include "assignmentList.h"

int main(int argc, char **argv) {
	QApplication app (argc, argv);

	AssignmentList window;

	return app.exec();
}
