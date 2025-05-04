import QtQuick
import QtQuick.Controls
import QtWebSockets

ApplicationWindow {
  visible: true
  width: 600
  height: 600
  title: "Minesweeper Final"

  property var sessions: []
  property int connectedClients: 0

  WebSocket {
    id: webSocket
    url: "ws://127.0.0.1:1234"
    active: true

    onTextMessageReceived: function (message) {
      console.log("Received: " + message)
      var data = JSON.parse(message)

      if (data.type === "clientCount") {
        connectedClients = data.count
      } else if (data.type === "sessionList") {
        sessions = data.sessions
      } else if (data.type === "newGame" || (data.type === "sessionJoined"
                                             && data.bombs !== undefined)) {
        var boardPageInstance = boardPageComponent.createObject(stackView)
        boardPageInstance.rows = data.rows
        boardPageInstance.cols = data.cols
        boardPageInstance.bombs = data.bombs.length
            || data.bombs // handle both array and int
        boardPageInstance.bombList = data.bombs
        boardPageInstance.ready = true
        stackView.push(boardPageInstance)

        if (data.type === "newGame") {
          console.log("New game started")
        } else {
          console.log("Joined session after game started")
        }
      } else if (data.type === "sessionJoined") {
        console.log("Joined session, waiting for more players...")
        // Optionally show waiting UI
      }
    }
  }

  StackView {
    id: stackView
    anchors.fill: parent
    initialItem: LandingPage {
      socket: webSocket
      onStartGame: stackView.push(startPageComponent)
      onJoinGame: {
        webSocket.sendTextMessage(JSON.stringify({
                                                   "type": "getSessions"
                                                 }))
        stackView.push(joinPageComponent)
      }
    }
  }

  Component {
    id: startPageComponent
    StartSessionPage {
      socket: webSocket
      onBack: stackView.pop()
    }
  }

  Component {
    id: joinPageComponent
    JoinSessionPage {
      socket: webSocket
      sessionList: sessions
      onBack: stackView.pop()
    }
  }

  Component {
    id: boardPageComponent
    BoardPage {}
  }
}
