import QtQuick 1.0

Rectangle
{
    id: game
    color: 'blue'
    
    Item {
        id: main
        
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 400
        anchors.margins: 20
        
        Rectangle {
            color: 'red'
            id: board
            objectName: 'board'
            anchors.fill: parent
        }
        
        Rectangle {
            color: 'green'
            id: options
            anchors.fill: parent
            
            ListModel {
                id: fruitModel

                ListElement { name: "Apple";  cost: 2.45 }
                ListElement { name: "Orange"; cost: 3.25 }
                ListElement { name: "Banana"; cost: 1.95 }
            }
            
            Row {
                anchors.fill: parent
                
                Column {
                    Text { text: "Themes:" }
                    
                    Repeater {
                        model: fruitModel
                        Text { text: fruitModel.get(index).name }
                    }
                }
                
                Column {
                    Text { text: "Players:" }
                    
                    Repeater {
                        model: fruitModel
                        Text { text: fruitModel.get(index).cost }
                    }
                }
            }
        }
    }
    
    Component.onCompleted: game.state="newgame"
    
    Column {
        anchors.margins:20
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: main.left
        anchors.left: parent.left
        
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            
            text: "New Game"
            onClicked: game.state="newgame"
        }
        
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            
            text: "Play"
            onClicked: game.state="playing"
        }
    }
    
    states: [
         State {
             name: "newgame"
             PropertyChanges { target: board; visible: false }
             PropertyChanges { target: options; visible: true }
         },
         
         State {
             name: "playing"
             PropertyChanges { target: board; visible: true }
             PropertyChanges { target: options; visible: false }
         }
     ]
}