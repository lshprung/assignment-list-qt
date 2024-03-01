#ifndef GROUP_H
#define GROUP_H

#include <QString>
#include <QVBoxLayout>

class Group : public QVBoxLayout {
	Q_OBJECT

	public:
		int id;
		QString name;
		QString column;
		QString link;
		bool hidden;

		Group(
				int id, 
				QString name, 
				QString column = "left", 
				QString link = "", 
				bool hidden = false
			 );

	private slots:
		void showContextMenu();
		void addEntry();
		void editGroup();
		void removeGroup();
};

#endif
