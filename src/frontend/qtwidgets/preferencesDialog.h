#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>

#include "ui_preferencesDialog.h"

// set configuration options in the program
class PreferencesDialog : public QDialog {
	Q_OBJECT

	public:
		PreferencesDialog();

	private:
		Ui::preferencesDialog ui;
		QDialog::DialogCode ret_value = QDialog::Rejected;

		void setupPathsTab();

	private slots:
		void dbPathDialog();
		void close();
		void apply();
		void reload();
};

#endif
