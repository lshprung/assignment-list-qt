#include <QComboBox>
#include <QDate>
#include <QDateTimeEdit>
#include <QLineEdit>

#include "rule.h"

Rule::Rule(int id, int entry_id, When when, QDateTime date, QString color, QString highlight) :
	id(id),
	entry_id(entry_id),
	when(when),
	date(date),
	color(color),
	highlight(highlight)
{
	QComboBox *when_widget = new QComboBox;
	QDateTimeEdit *date_widget = new QDateTimeEdit(QDate::currentDate());
	QLineEdit *color_widget = new QLineEdit; // TODO consider making this a color selector widget
	QLineEdit *highlight_widget = new QLineEdit; // TODO consider making this a color selector widget

	QStringList when_options;
	when_options.append("Before");
	when_options.append("After");
	when_widget->addItems(when_options);
	when_widget->setCurrentIndex(this->when);
	this->addWidget(when_widget);

	date_widget->setDisplayFormat("MM/dd/yyyy");
	date_widget->setDateTime(this->date);
	this->addWidget(date_widget);

	this->addStretch();

	color_widget->setPlaceholderText("Color");
	if(!this->color.isEmpty())
		color_widget->setText(this->color);
	this->addWidget(color_widget);

	highlight_widget->setPlaceholderText("Highlight");
	if(!this->highlight.isEmpty())
		highlight_widget->setText(this->highlight);
	this->addWidget(highlight_widget);
}
