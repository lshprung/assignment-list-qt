#include <QMessageBox>

#include "backend/db_sqlite.h"
#include "editGroupForm.h"

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
	group.name = ui.group_name->text();
	group.column = Group::Column(ui.group_column->currentIndex());
	group.link = ui.group_link->text();
	QMessageBox error_message;
	BackendDB database;

	if(group.name.isEmpty()) {
		error_message.setIcon(QMessageBox::Warning);
		error_message.setWindowTitle("Error Message");
		error_message.setText("Name cannot be blank");
		error_message.exec();
		return;
	}

	database.updateGroup(this->group);

	QDialog::accept();
}
