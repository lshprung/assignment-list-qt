#include <QFileDialog>
#include <QSettings>

#include "preferencesDialog.h"

PreferencesDialog::PreferencesDialog() {
	// load uic
	ui.setupUi(this);

	// display widgets
	// TODO make this a scollable window
	// FIXME could use some work on sizing
	this->setupPathsTab();

	// create button connections
	QObject::connect(ui.close_button, &QPushButton::released, this, &PreferencesDialog::close);
	QObject::connect(ui.apply_button, &QPushButton::released, this, &PreferencesDialog::apply);
	QObject::connect(ui.reload_button, &QPushButton::released, this, &PreferencesDialog::reload);
}

void PreferencesDialog::setupPathsTab() {
	QSettings settings;
	settings.beginGroup("paths");

	ui.db_path_edit->setText(settings.value("db_path").toString());
	QObject::connect(ui.db_path_button, &QPushButton::released, this, &PreferencesDialog::dbPathDialog);
}

void PreferencesDialog::dbPathDialog() {
	QFileDialog file_dialog;
	// TODO create filter to only allow selecting .db files
	QString new_path = file_dialog.getOpenFileName(this, "Open File");

	if(!new_path.isEmpty())
		ui.db_path_edit->setText(new_path);
}

// close the dialog, returning our ret_value
void PreferencesDialog::close() {
	this->done(ret_value);
}

// update the configuration in the config file
void PreferencesDialog::apply() {
	QSettings settings;

	// save paths
	settings.beginGroup("paths");
	settings.setValue("db_path", ui.db_path_edit->text());

	// set the return value to accepted
	this->ret_value = QDialog::Accepted;
}

// update, reload, and close the window
void PreferencesDialog::reload() {
	this->apply();
	this->accept();
}
