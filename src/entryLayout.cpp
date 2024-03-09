#include <QLabel>

#include "entryLayout.h"

EntryLayout::EntryLayout(const Entry &e) :
	entry(e)
{
	QLabel *bullet = new QLabel();
	QLabel *body = new QLabel();

	// set styling
	this->setContentsMargins(2, 2, 2, 2);

	bullet->setFont(QFont("Arial", 11));
	bullet->setMaximumWidth(15);

	body->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse);
	body->setFont(QFont("Arial", 11));
	body->setWordWrap(true);
	body->setToolTip("Right-Click for actions");

	// Check rules
	// TODO

	// set conditional styling
	if(this->entry.done) {
		bullet->setText("\u2713");
		/*
		bullet->setStyleSheet(
				"QLabel {"
				"	color: green;"
				"}"
				);
		*/
	}
	else
		bullet->setText("- ");
	this->addWidget(bullet);

	if(!this->entry.due.isNull())
		body->setText(this->entry.due.toString("MM/dd/yyyy: "));
	else if(!this->entry.due_alt.isEmpty())
		body->setText(this->entry.due_alt + ": ");

	if(!this->entry.link.isEmpty()) {
		body->setOpenExternalLinks(true);
		body->setText(body->text() + "<a href=\"" + this->entry.link.toString() + "\" " "style=\"color: " + (this->entry.color.isEmpty() ? "default" : this->entry.color ) + ";\">");
	}
	body->setText(body->text() + this->entry.desc);
	if(!this->entry.link.isEmpty()) {
		body->setText(body->text() + "</a>");
		body->setToolTip(this->entry.link.toString());
	}

	if(this->entry.done) {
		QFont body_font = body->font();
		body_font.setStrikeOut(true);
		body->setFont(body_font);
		/*
		body->setStyleSheet(
				"QLabel {"
				"	color: green"
				"}"
				);
		*/
	}
	else {
		/*
		body->setStyleSheet(
				"QLabel {"
				"	color: " + (this->color.isEmpty() ? "default" : this->color) + ";"
				"	background-color: " + (this->highlight.isEmpty() ? "none" : this->highlight) + ";"
				"	font-weight: " + (this->due.isValid() && this->due <= QDateTime::currentDateTime() ? "bold" : "normal") + ";"
				";"
				);
		*/
	}
	this->addWidget(body);
}
