#include "backend/db_sqlite.h"
#include "edit_entry_form.h"

EditEntryForm::EditEntryForm(const Entry &e) :
	entry(e)
{
	// load uic
	ui.setupUi(this);

	// set titles
	this->setWindowTitle("Edit Entry");
	ui.title->setText("Edit Entry");

	// widgets setup
}
