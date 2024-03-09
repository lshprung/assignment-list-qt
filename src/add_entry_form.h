#ifndef ADDENTRYFORM_H
#define ADDENTRYFORM_H

#include <QObject>

#include "group.h"
#include "ui_entry_form.h"

class AddEntryForm : public QDialog {
	Q_OBJECT

	public:
		AddEntryForm(const Group &g);

	private:
		Ui::entryDialog ui;

		Group parent_group;

	private slots:
		void accept();
};

#endif
