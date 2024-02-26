#include <QMessageBox>

#include "add_group_form.h"

AddGroupForm::AddGroupForm() {
	// load uic
	ui.setupUi(this);

	// setup dialog button connections
	QObject::connect(ui.buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
	QObject::connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &AddGroupForm::handleSubmit);
}

void AddGroupForm::handleSubmit() {
	QString name_text = ui.new_group_name->text();
	QString column_text = ui.new_group_column->currentText();
	QString link_text = ui.new_group_link->text();
	QMessageBox error_message;

	if(name_text.isEmpty()) {
		error_message.setIcon(QMessageBox::Warning);
		error_message.setWindowTitle("Error Message");
		error_message.setText("Name cannot be blank");
		error_message.setParent(this);
		error_message.show();
	}

	// TODO insert into database
	this->close();
}
