import QtQuick
import QtQuick.Controls
import "BoardLogic.js" as BoardLogic

Item {
    id: boardPage

    property var game: ({})
    property bool running: false
    property var currentGame: ({})

    onGameChanged: {
        boardLoader.source = `${game.gameType}Board.qml`
    }

    Loader {
        id: boardLoader
        anchors.fill: parent
        // sync vars
        Binding {
            target: boardPage
            property: "running"
            value: boardLoader.item.running
            when: boardLoader.status === Loader.Ready
        }

        Binding {
            target: boardLoader.item
            property: "game"
            value: boardPage.game
            when: boardLoader.status === Loader.Ready
        }

        Binding {
            target: boardLoader.item
            property: "currentGame"
            value: boardPage.currentGame
            when: boardLoader.status === Loader.Ready
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#AA000000"
        visible: !boardPage.running
        MouseArea {
            anchors.fill: parent
        }
    }
}
