#include <QMessageBox>

#include <QDebug>

#include "addGroupForm.h"
#include "backend/db_sqlite.h"

AddGroupForm::AddGroupForm() {
	// load uic
	ui.setupUi(this);

	// set titles
	this->setWindowTitle("Add Group");
	ui.title->setText("Add Group");
}

void AddGroupForm::accept() {
	QString name_text = ui.group_name->text();
	Group::Column column_value = Group::Column(ui.group_column->currentIndex());
	QString link_text = ui.group_link->text();
	QMessageBox error_message;
	BackendDB database;
	int new_id;

	if(name_text.isEmpty()) {
		qDebug() << "Gets here";
		error_message.setIcon(QMessageBox::Warning);
		error_message.setWindowTitle("Error Message");
		error_message.setText("Name cannot be blank");
		error_message.exec();
		return;
	}

	new_id = database.insertGroup(Group(0, name_text, column_value, link_text));

	QDialog::accept();
}
