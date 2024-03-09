#include <QComboBox>
#include <QDate>
#include <QDateTimeEdit>
#include <QLineEdit>

#include "ruleLayout.h"

RuleLayout::RuleLayout(const Rule &r) :
	rule(r)
{
	QComboBox *when_widget = new QComboBox;
	QDateTimeEdit *date_widget = new QDateTimeEdit(QDate::currentDate());
	QLineEdit *color_widget = new QLineEdit; // TODO consider making this a color selector widget
	QLineEdit *highlight_widget = new QLineEdit; // TODO consider making this a color selector widget

	QStringList when_options;
	when_options.append("Before");
	when_options.append("After");
	when_widget->addItems(when_options);
	when_widget->setCurrentIndex(this->rule.when);
	this->addWidget(when_widget);

	date_widget->setDisplayFormat("MM/dd/yyyy");
	date_widget->setDateTime(this->rule.date);
	this->addWidget(date_widget);

	this->addStretch();

	color_widget->setPlaceholderText("Color");
	if(!this->rule.color.isEmpty())
		color_widget->setText(this->rule.color);
	this->addWidget(color_widget);

	highlight_widget->setPlaceholderText("Highlight");
	if(!this->rule.highlight.isEmpty())
		highlight_widget->setText(this->rule.highlight);
	this->addWidget(highlight_widget);
}
