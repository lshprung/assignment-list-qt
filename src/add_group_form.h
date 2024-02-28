#ifndef ADDGROUPFORM_H
#define ADDGROUPFORM_H

#include "ui_add_group_form.h"

class AddGroupForm : public QDialog {
	Q_OBJECT

	public:
		AddGroupForm();

	private:
		Ui::Dialog ui;

	private slots:
		void accept();
};

#endif
