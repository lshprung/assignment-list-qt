#include <QMessageBox>

#include "../../backend/db_sqlite.h"
#include "editEntryForm.h"

EditEntryForm::EditEntryForm(const Entry &e) :
	entry(e)
{
	// load uic
	ui.setupUi(this);

	// set titles
	this->setWindowTitle("Edit Entry");
	ui.title->setText("Edit Entry");

	// widgets setup
	ui.entry_desc->setText(this->entry.desc);
	ui.entry_due->setDate(QDate::currentDate());
	if(this->entry.due.isValid()) {
		ui.entry_due->setDate(entry.due.date());
		ui.entry_due_checkbox->setChecked(true);
	}
	else
		ui.entry_due_checkbox->setChecked(false);
	ui.entry_due_alt->setText(this->entry.due_alt);
	ui.entry_link->setText(this->entry.link.toString());
	ui.entry_color->setText(this->entry.color);
	ui.entry_highlight->setText(this->entry.highlight);
}

void EditEntryForm::accept() {
	this->entry.desc = ui.entry_desc->text();
	if(ui.entry_due_checkbox->isChecked())
		this->entry.due = ui.entry_due->dateTime();
	else
		this->entry.due = QDateTime();
	this->entry.due_alt = ui.entry_due_alt->text();
	this->entry.link = ui.entry_link->text();
	this->entry.color = ui.entry_color->text();
	this->entry.highlight = ui.entry_highlight->text();
	QMessageBox error_message;
	BackendDB database;

	if(this->entry.desc.isEmpty()) {
		error_message.setIcon(QMessageBox::Warning);
		error_message.setWindowTitle("Error Message");
		error_message.setText("Name cannot be blank");
		error_message.exec();
		return;
	}

	database.updateEntry(this->entry);

	QDialog::accept();
}
