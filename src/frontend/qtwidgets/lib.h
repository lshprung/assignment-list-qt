/* Helper functions that various classes utilize */

#include <QMainWindow>

#include "assignmentList.h"

AssignmentList *getMainWindow();

QDialog *getParentDialog();

// used to clear out a layout when a refresh occurs
void recursiveClear(QLayout *layout);
