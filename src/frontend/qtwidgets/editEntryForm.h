#ifndef EDITENTRYFORM_H
#define EDITENTRYFORM_H

#include <QDialog>

#include "entry.h"
#include "ui_entryForm.h"

// form to edit/update an entry
class EditEntryForm : public QDialog {
	Q_OBJECT

	public:
		EditEntryForm(const Entry &e);

	private:
		Ui::entryDialog ui;

		Entry entry;

	private slots:
		void accept();
};

#endif
