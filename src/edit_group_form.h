#ifndef EDITGROUPFORM_H
#define EDITGROUPFORM_H

#include <QDialog>

#include "group.h"
#include "ui_group_form.h"

// form to edit/update a group
class EditGroupForm : public QDialog {
	Q_OBJECT

	public:
		EditGroupForm(const Group &g);

	private:
		Ui::groupDialog ui;

		Group group;

	private slots:
		void accept();
};

#endif
