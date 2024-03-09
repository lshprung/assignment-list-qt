#include <QDate>
#include <QMessageBox>
#include <QString>

#include "addEntryForm.h"
#include "backend/db_sqlite.h"

AddEntryForm::AddEntryForm(const Group &g) :
	parent_group(g)
{
	// load uic
	ui.setupUi(this);

	// set titles
	this->setWindowTitle("Add Entry");
	ui.title->setText("Add Entry");

	// widgets setup
	ui.entry_due->setDate(QDate::currentDate());
}

void AddEntryForm::accept() {
	QString desc_text = ui.entry_desc->text();
	QDateTime due_text = ui.entry_due->date().startOfDay();
	QString due_alt_text = ui.entry_due_alt->text();
	QString link_text = ui.entry_link->text();
	QString color_text = ui.entry_color->text();
	QString highlight_text = ui.entry_highlight->text();
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
	if(!ui.entry_due_checkbox->isChecked())
		due_text = QDateTime();

	new_id = database.insertEntry(Entry(0, this->parent_group.id, desc_text, due_text, due_alt_text, link_text, color_text, highlight_text));

	QDialog::accept();
}
