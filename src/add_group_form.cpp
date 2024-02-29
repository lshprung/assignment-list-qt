#include <QMessageBox>

#include <QDebug>

#include "add_group_form.h"
#include "backend/db_sqlite.h"

AddGroupForm::AddGroupForm() {
	// load uic
	ui.setupUi(this);
}

void AddGroupForm::accept() {
	QString name_text = ui.new_group_name->text();
	QString column_text = ui.new_group_column->currentText();
	QString link_text = ui.new_group_link->text();
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

	new_id = database.insertGroup(Group(0, name_text, column_text, link_text));
	// TODO redraw the main window

	QDialog::accept();
}
