import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Window {
	width: 640
	height: 480
	visible: true
	// TODO grab this from config.h
	title: PROJECT_TITLE

	// DropDown for groups (including an "all" option)
	Item {
		width: parent.width
		height: 50
		ComboBox {
			anchors.fill: parent
			id: groupComboBox
			model: [
				"all"
				//...
			]
		}
	}
}
