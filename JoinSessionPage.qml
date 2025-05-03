import QtQuick
import QtQuick.Controls

Item {
    signal back
    property var socket
    property var sessionList: [] // This just receives the data, no binding

    Column {
        anchors.centerIn: parent
        spacing: 10

        Repeater {
            model: sessionList // Just using the received sessionList directly
            delegate: Row {
                spacing: 10

                Text {
                    text: "Session " + modelData.id + ": " + modelData.playersJoined + "/"
                          + modelData.maxPlayers + " (" + modelData.rows + "x"
                          + modelData.cols + ", " + modelData.bombs + " bombs)"
                }

                Button {
                    text: "Join"
                    onClicked: socket.sendTextMessage(JSON.stringify({
                                                                         "type": "joinSession",
                                                                         "sessionId": modelData.id
                                                                     }))
                }
            }
        }

        Button {
            text: "Back"
            onClicked: back()
        }
    }
}
