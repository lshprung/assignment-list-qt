#ifndef RULESDIALOG_H
#define RULESDIALOG_H

#include <QDialog>

#include "entry.h"
#include "rule.h"
#include "ui_rulesDialog.h"

// show the list of rules associated with an entry
class RulesDialog : public QDialog {
	Q_OBJECT

	public:
		RulesDialog(const Entry &entry);
		void drawRules();

	private:
		Ui::rulesDialog ui;
		int entry_id;
		QList<Rule *> rules;

		void updateRulesList();

	private slots:
		void addRule();
		void deleteRule(int i);
};

#endif
