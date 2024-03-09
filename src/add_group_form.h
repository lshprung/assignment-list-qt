#ifndef ADDGROUPFORM_H
#define ADDGROUPFORM_H

#include <QObject>

#include "ui_group_form.h"

class AddGroupForm : public QDialog {
	Q_OBJECT

	public:
		AddGroupForm();

	private:
		Ui::groupDialog ui;

	private slots:
		void accept();
};

#endif
