
#include "lib.h"
#include "ruleLayout.h"

RuleLayout::RuleLayout(const Rule &r) :
	rule(r)
{
	this->when_widget = new QComboBox;
	this->date_widget = new QDateTimeEdit(QDate::currentDate());
	this->date_widget->setCalendarPopup(true);
	this->color_widget = new QLineEdit;
	this->highlight_widget = new QLineEdit;
	this->del_button = new QPushButton;

	QStringList when_options;
	when_options.append("Before");
	when_options.append("After");
	this->when_widget->addItems(when_options);
	this->when_widget->setCurrentIndex(this->rule.when);
	this->addWidget(this->when_widget);

	this->date_widget->setDisplayFormat("MM/dd/yyyy");
	this->date_widget->setDateTime(this->rule.date);
	this->addWidget(this->date_widget);

	this->addStretch();

	this->color_widget->setPlaceholderText("Color");
	if(!this->rule.color.isEmpty())
		this->color_widget->setText(this->rule.color);
	this->addWidget(this->color_widget);

	this->highlight_widget->setPlaceholderText("Highlight");
	if(!this->rule.highlight.isEmpty())
		this->highlight_widget->setText(this->rule.highlight);
	this->addWidget(this->highlight_widget);

	this->del_button->setText("Delete");
	// connection needs to be made in rulesDialog.cpp
	this->addWidget(this->del_button);
}
