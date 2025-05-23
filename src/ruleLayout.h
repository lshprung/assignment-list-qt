#ifndef RULELAYOUT_H
#define RULELAYOUT_H

#include <QComboBox>
#include <QDate>
#include <QDateTimeEdit>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "rule.h"

class RuleLayout : public QHBoxLayout {
	Q_OBJECT

	public:
		Rule rule;
		QComboBox *when_widget;
		QDateTimeEdit *date_widget;
		QLineEdit *color_widget; // TODO consider making this a color selector widget
		QLineEdit *highlight_widget; // TODO consider making this a color selector widget
		QPushButton *del_button;

		RuleLayout(const Rule &r);

	private slots:
		void toggle_date_enabled();
};

#endif
