import QtQuick
import QtQuick.Controls

Item {
    signal back()
    property var socket

    Column {
        anchors.centerIn: parent
        spacing: 10

        Row {
            spacing: 5
            Label { text: "Rows:" }
            SpinBox { id: rowsInput; from: 5; to: 20; value: 10 }
        }

        Row {
            spacing: 5
            Label { text: "Cols:" }
            SpinBox { id: colsInput; from: 5; to: 20; value: 10 }
        }

        Row {
            spacing: 5
            Label { text: "Bombs:" }
            SpinBox { id: bombsInput; from: 1; to: 100; value: 15 }
        }

        Row {
            spacing: 5
            Label { text: "Players:" }
            SpinBox { id: playersInput; from: 1; to: 4; value: 2 }
        }

        Button {
            text: "Create Session"
            onClicked: socket.sendTextMessage(JSON.stringify({
                type: "createSession",
                rows: rowsInput.value,
                cols: colsInput.value,
                bombs: bombsInput.value,
                players: playersInput.value
            }))
        }

        Button {
            text: "Back"
            onClicked: back()
        }
    }
}
