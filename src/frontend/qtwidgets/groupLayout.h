#ifndef GROUPLAYOUT_H
#define GROUPLAYOUT_H

#include <QVBoxLayout>

#include "group.h"

class GroupLayout : public QVBoxLayout {
	Q_OBJECT

	public:
		Group group;

		GroupLayout(const Group &g);

	private slots:
		void showContextMenu();
		void addEntry();
		void editGroup();
		void removeGroup();
};

#endif
