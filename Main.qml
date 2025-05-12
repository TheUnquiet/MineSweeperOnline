import QtQuick
import QtQuick.Controls
import QtWebSockets

ApplicationWindow {
  visible: true
  width: 600
  height: 600
  title: "Minesweeper Final"

  property int connectedClients: 0

  WebSocket {
    id: webSocket
    url: "ws://127.0.0.1:1234"
    active: true

    onTextMessageReceived: function (message) {
      console.log("Received: " + message)
      var data = JSON.parse(message)

      switch (data.type) {
      case "clientCount":
        connectedClients = data.count
        break
      case "sessionList":
        var joinPageInstance = joinPageComponent.createObject(stackView, {
                                                                "sessionList": data.sessions,
                                                                "socket": webSocket
                                                              })
        stackView.push(joinPageInstance)
        break
      case "newGame":
        console.log("New game started")
        stackView.currentItem.currentGame = data
        break
      case "sessionJoined":
        console.log("Joined session, waiting for more players...")
        var boardPageInstance = boardPageComponent.createObject(stackView, {
                                                                  "game": data
                                                                })
        stackView.push(boardPageInstance)
        break
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
      onBack: stackView.pop()
    }
  }

  Component {
    id: boardPageComponent
    BoardPage {}
  }
}
