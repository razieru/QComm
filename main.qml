import QtQuick 2.0
import QtQuick.Controls 2.12
import DatagramModel 1.0
import Listener 1.0
import QtQuick.Controls.Material 2.0

ApplicationWindow {
	width: 640
	height: 480
	visible: true
	title: qsTr("QComm")
	DatagramModel{
		id: dataModel
		separator: "55aa"
	}
	Listener {
		id: reader
		host: "192.168.11.242"
		port: 12000
		model: dataModel
	}
	Action {
		shortcut: "Ctrl++"
		onTriggered: ++fontSize
	}
	Action {
		shortcut: "Ctrl+-"
		onTriggered: --fontSize
	}
	Action {
		shortcut: "Space"
		onTriggered: reader.active = !reader.active
	}
	Action {
		shortcut: "Ctrl+F"
		onTriggered: filterDialog.open()
	}

	property int fontSize: 14
	property string filter: ""

	function replacer(match,p1,p2,p3) {
		return "<b style=\"background-color: steelblue; color: white\">"+match+"</b>"
	}

	function replaceAll(str, find) {
		return str.replace(new RegExp(find, 'g'), replacer);
	}

	ListView {
		id: listView
		anchors.fill: parent
		model: dataModel
		delegate: ItemDelegate {
			width: listView.width
			height: 24
			Label {
				id: dataLabel
				height: 24
				width: parent.width
				text: {
					if (filter) {
						return replaceAll(model.display,filter.toLocaleLowerCase())
					}
					return model.display
				}
//				width: listView.width
				font.capitalization: Font.AllUppercase
				font.family: "Roboto Mono"
				font.weight: Font.Thin
				font.pointSize: fontSize
				textFormat: Text.RichText
			}
		}
		onCountChanged: {
			positionViewAtEnd()
		}

	}

	//	MouseArea {
	//		anchors.fill: parent
	//		acceptedButtons: Qt.NoButton
	//		onWheel: print(wheel.y)//if (ctrlPressed) print(wheel.y)
	//		property bool ctrlPressed: false
	//		Keys.onPressed: {
	//			print("WWW")
	//			if (event.key === Qt.Key_Control)
	//				ctrlPressed = true
	//		}
	//		Keys.onCancelPressed: {
	//			print("qqqprint(wheel.y)")
	//			if (event.key === Qt.Key_Control)
	//				ctrlPressed = false
	//		}
	//	}

	Column {
		anchors {
			bottom: parent.bottom
			right: parent.right
		}
		RoundButton {
			visible: scale
			Behavior on scale {NumberAnimation{easing.type: Easing.InOutCubic}}
			scale: listView.count ? 1 : 0
			onClicked: dataModel.clear()
		}
		RoundButton {
			Material.background: reader.active ? "green" : "red"
			onClicked: reader.active = reader.active ? false : true
		}
		RoundButton {
			Material.background: "cornflowerblue"
			onClicked: dialog.open()
		}
	}
	Dialog {
		id: filterDialog
		anchors.centerIn: parent

		TextField{
			id: filterInput
			placeholderText: "Filter String"
			selectByMouse: true
			selectionColor: "indianred"
			text: filter
			onTextChanged: filter = text
			//			onEditingFinished: filter = text
		}
		onOpened: filterInput.forceActiveFocus()
	}

	Dialog {
		id: dialog
		anchors.centerIn: parent
		Column {
			TextField {
				text: reader.host
				placeholderText: "IP"
				onEditingFinished: reader.host = text
				validator: RegExpValidator { regExp: /(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)/ }
				selectByMouse: true
				selectionColor: "indianred"
			}
			TextField {
				text: reader.port
				placeholderText: "Port"
				validator: IntValidator {bottom:0; top:65535}
				onEditingFinished: reader.port = parseInt(text)
				selectByMouse: true
				selectionColor: "indianred"
			}
			TextField {
				text: dataModel.separator
				placeholderText: "Separator"
				onEditingFinished: dataModel.separator
				selectByMouse: true
				selectionColor: "indianred"
			}
		}

	}
}
