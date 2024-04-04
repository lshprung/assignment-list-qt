#ifndef ENTRYLAYOUT_H
#define ENTRYLAYOUT_H

#include <QDateTime>
#include <QHBoxLayout>
#include <QString>
#include <QUrl>

#include "entry.h"
#include "rule.h"

class EntryLayout : public QHBoxLayout {
	Q_OBJECT

	public:
		Entry entry;

		EntryLayout(const Entry &e);

	private:
		QList<Rule> loadRules();

	private slots:
		void showContextMenu();
		void editEntry();
		void setRules();
		void toggleDone();
		void cloneEntry();
		void removeEntry();
};

#endif
