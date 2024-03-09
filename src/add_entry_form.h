#ifndef ADDENTRYFORM_H
#define ADDENTRYFORM_H

#include <QObject>

#include "ui_entry_form.h"

class AddEntryForm : public QDialog {
	Q_OBJECT

	public:
		AddEntryForm(int parent_id);

	private:
		Ui::entryDialog ui;

		int parent_id;

	private slots:
		void accept();
};

#endif
