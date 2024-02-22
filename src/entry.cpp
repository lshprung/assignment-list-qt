#include <QLabel>

#include "entry.h"

Entry::Entry(int id, int parent_id, QString desc, QDateTime due, QString due_alt, QUrl link, QString color, QString highlight, bool done, bool hidden) :
	id(id),
	parent_id(parent_id),
	desc(desc),
	due(due),
	due_alt(due_alt),
	link(link),
	color(color),
	highlight(highlight),
	done(done),
	hidden(hidden) 
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
	if(this->done) {
		bullet->setText("\u2713");
		bullet->setStyleSheet(
				"QLabel {"
				"	color: green;"
				"}"
				);
	}
	else
		bullet->setText("- ");
	this->addWidget(bullet);

	if(!this->due.isNull())
		body->setText(this->due.toString("M/d/yyyy"));
	else if(!this->due_alt.isEmpty())
		body->setText(this->due_alt + ": ");

	if(!this->link.isEmpty()) {
		body->setOpenExternalLinks(true);
		body->setText(body->text() + "<a href=\"" + this->link.toString() + "\" " "style=\"color: " + (this->color.isEmpty() ? "default" : this->color ) + ";\">");
	}
	body->setText(body->text() + this->desc);
	if(!this->link.isEmpty()) {
		body->setText(body->text() + "</a>");
		body->setToolTip(this->link.toString());
	}

	if(this->done) {
		QFont body_font = body->font();
		body_font.setStrikeOut(true);
		body->setFont(body_font);
		body->setStyleSheet(
				"QLabel {"
				"	color: green"
				"}"
				);
	}
	else {
		body->setStyleSheet(
				"QLabel {"
				"	color: " + (this->color.isEmpty() ? "default" : this->color) + ";"
				"	background-color: " + (this->highlight.isEmpty() ? "none" : this->highlight) + ";"
				"	font-weight: " + (this->due.isValid() && this->due <= QDateTime::currentDateTime() ? "bold" : "normal") + ";"
				";"
				);
	}
	this->addWidget(body);
}
