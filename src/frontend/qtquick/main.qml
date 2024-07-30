import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
	width: 640
	height: 480
	visible: true
	title: PROJECT_TITLE
	
	id: root

	Drawer {
		id: drawer

		width: Math.min(root.width, root.height) / 3 * 2
		height: root.height

		ListView {
			currentIndex: -1
			anchors.fill: parent

			delegate: ItemDelegate {
				width: parent.width
				text: model.text
				highlighted: ListView.isCurrentItem
				onClicked: {
					drawer.close()
					model.triggered()
				}
			}

			model: ListModel {
				ListElement {
					text: qsTr("Preferences...")
					triggered: function() { preferencesDialog.open(); }
				}
				ListElement {
					text: qsTr("Reload...")
					triggered: function() { /* reload from database */ }
				}
				ListElement {
					text: qsTr("About...")
					triggered: function() { aboutDialog.open() }
				}
			}

			ScrollIndicator.vertical: ScrollIndicator { }
		}
	}

	header: ToolBar {
		ToolButton {
			id: menuButton
			anchors.left: parent.left
			anchors.verticalCenter: parent.verticalCenter
			// TODO create icon for the drawer
			//icon.source: "..."
			onClicked: drawer.open()
		}
		Label {
			anchors.centerIn: parent
			// TODO determine what title to set
			//text: ...
			font.pixelSize: 20
			elide: Label.ElideRight
		}
	}


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
