#include <QDate>
#include <QMessageBox>
#include <QString>

#include "add_entry_form.h"
#include "backend/db_sqlite.h"

AddEntryForm::AddEntryForm(int parent_id) :
	parent_id(parent_id)
{
	// load uic
	ui.setupUi(this);

	// widgets setup
	ui.new_entry_due->setDate(QDate::currentDate());
}

void AddEntryForm::accept() {
	QString desc_text = ui.new_entry_desc->text();
	QDateTime due_text = ui.new_entry_due->date().startOfDay();
	QString due_alt_text = ui.new_entry_due_alt->text();
	QString link_text = ui.new_entry_link->text();
	QString color_text = ui.new_entry_color->text();
	QString highlight_text = ui.new_entry_highlight->text();
	QMessageBox error_message;
	BackendDB database;
	int new_id;

	// Check that the new entry is not blank
	if(desc_text.isEmpty()) {
		error_message.setIcon(QMessageBox::Warning);
		error_message.setWindowTitle("Error Message");
		error_message.setText("Description cannot be blank");
		error_message.exec();
		return;
	}

	// replace due_text with null date if due_checkbox is unchecked
	if(!ui.new_entry_due_checkbox->isChecked())
		due_text = QDateTime();

	new_id = database.insertEntry(Entry(0, this->parent_id, desc_text, due_text, due_alt_text, link_text, color_text, highlight_text));

	QDialog::accept();
}
