#ifndef ENTRYLAYOUT_H
#define ENTRYLAYOUT_H

#include <QDateTime>
#include <QHBoxLayout>
#include <QString>
#include <QUrl>

#include "entry.h"

class EntryLayout : public QHBoxLayout {
	Q_OBJECT

	public:
		Entry entry;

		EntryLayout(const Entry &e);

	private slots:
		void showContextMenu();
		void editEntry();
		void setRules();
		void toggleDone();
		void removeEntry();
};

#endif
