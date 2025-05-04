import QtQuick
import QtQuick.Controls
import "BoardLogic.js" as BoardLogic

Item {
    id: boardPage
    width: parent ? parent.width : 600
    height: parent ? parent.height : 600

    property int rows: 0
    property int cols: 0
    property int bombs: 0
    property var grid: []
    property bool ready: false
    property var bombList: []

    Loader {
        id: boardLoader
        anchors.fill: parent
        active: ready
        sourceComponent: boardComponent
    }

    Component {
        id: boardComponent
        Board {
            id: board
            rows: boardPage.rows
            cols: boardPage.cols
            bombs: boardPage.bombs
            grid: boardPage.grid

            Component.onCompleted: {
                Qt.callLater(() => {
                                 BoardLogic.initGameFromServer(
                                     board, rows, cols, boardPage.bombList,
                                     boardPage.grid, board.repeater)
                             })
            }
        }
    }
}
