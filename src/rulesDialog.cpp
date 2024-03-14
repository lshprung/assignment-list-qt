#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

#include <QDebug>

#include "backend/db_sqlite.h"
#include "lib.h"
#include "ruleLayout.h"
#include "rulesDialog.h"

RulesDialog::RulesDialog(const Entry &entry) {
	BackendDB database;

	this->entry_id = entry.id;

	// load uic
	ui.setupUi(this);

	// load rules into object member
	this->rules = database.loadRules(entry_id);

	// display widgets
	this->drawRules();

	// set connections
	QObject::connect(ui.add_rule_button, &QPushButton::released, this, &RulesDialog::addRule);
}

// for maintaining values when adding/removing rules
void RulesDialog::updateRulesList() {
	int i;

	for(i = 0; i < ui.rules_layout->children().size(); ++i) {
		this->rules[i]->when = Rule::When(qobject_cast<RuleLayout *>(ui.rules_layout->children()[i])->when_widget->currentIndex());
		this->rules[i]->date = qobject_cast<RuleLayout *>(ui.rules_layout->children()[i])->date_widget->dateTime();
		this->rules[i]->color = qobject_cast<RuleLayout *>(ui.rules_layout->children()[i])->color_widget->text();
		this->rules[i]->highlight = qobject_cast<RuleLayout *>(ui.rules_layout->children()[i])->highlight_widget->text();
	}
}

void RulesDialog::drawRules() {
	RuleLayout *new_layout;
	int i;


	// remove all children from layout
	recursiveClear(ui.rules_layout);

	// Draw each rule
	for(i = 0; i < this->rules.size(); ++i) {
		new_layout = new RuleLayout(*rules[i]);

		// connect delete button
		QObject::connect(new_layout->del_button, &QPushButton::released, this, [=](){ this->deleteRule(i); });

		ui.rules_layout->addLayout(new_layout);
	}
}

void RulesDialog::addRule() {
	// TODO handle in db backend to insert instead of updating if id is 0
	Rule *new_rule = new Rule(0, this->entry_id, Rule::before);
	RuleLayout *new_layout = new RuleLayout(*new_rule);

	// add new rule to the member variable
	this->rules.append(new_rule);

	// redraw rules
	this->updateRulesList();
	this->drawRules();
}

void RulesDialog::deleteRule(int i) {
	if(i < 0) return;
	if(i >= this->rules.size()) return;

	this->updateRulesList();
	this->rules.removeAt(i);
	this->drawRules();
}