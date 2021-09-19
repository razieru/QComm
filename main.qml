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
		host: "192.168.0.108"
		port: 10003
		model: dataModel
	}

	ListView {
		id: listView
		anchors.fill: parent
		model: dataModel
		delegate: TextInput {
			height: 24
			text: model.display
			width: listView.width
			font.capitalization: Font.AllUppercase
			font.family: "Roboto Mono"
			font.weight: Font.Thin
			font.pointSize: 14
			readOnly: true
			selectByMouse: true
			selectionColor: "indianred"
		}
		onCountChanged: {
			positionViewAtEnd()
		}

	}

	Column {
		anchors {
			bottom: parent.bottom
			right: parent.right
		}
		RoundButton {
			visible: listView.count
			onClicked: dataModel.clear()
		}
		RoundButton {
			Material.background: reader.active ? "green" : "red"
			onClicked: reader.active = reader.active ? false : true
		}
	}
}
