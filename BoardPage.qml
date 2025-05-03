import QtQuick
import QtQuick.Controls
import "BoardLogic.js" as BoardLogic

Item {
    id: boardPage
    width: parent ? parent.width : 600
    height: parent ? parent.height : 600

    property int rows: 10
    property int cols: 10
    property int bombs: 15
    property var grid: []
    property alias repeater: repeater

    Column {
        anchors.fill: parent
        spacing: 10
        padding: 20

        Button {
            text: "Restart"
            onClicked: BoardLogic.initGame()
        }

        Board {
            id: board
            rows: boardPage.rows
            cols: boardPage.cols
            bombs: boardPage.bombs
        }

        Repeater { id: repeater }
    }
}
