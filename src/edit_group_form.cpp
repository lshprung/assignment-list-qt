#include "edit_group_form.h"

EditGroupForm::EditGroupForm(const Group &g) :
	group(g)
{
	// load uic
	ui.setupUi(this);

	// set titles
	this->setWindowTitle("Edit Group");
	ui.title->setText("Edit Group");

	// widgets setup
	ui.group_name->setText(this->group.name);
	ui.group_column->setCurrentIndex(this->group.column);
	ui.group_link->setText(this->group.link);
}

void EditGroupForm::accept() {
}
