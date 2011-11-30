import QtQuick 1.0

Rectangle {
    id: gameSettings
    property string gameLanguage: 'en'
    property string gameType: 'image'
    
    color: 'green'
    signal gameStarted;
    
    onGameTypeChanged: themesModel.refresh(gameType, gameLanguage)
    
    Row {
        anchors.margins: 30
        anchors.fill: parent
        
        Column {
            height: parent.height
            Row {
                spacing: 20
                Button {
                    source: playersModel.iconsDir("gameicons/pairs.png")
                    text: "Pairs"
                    onClicked: gameType = 'image'
                }
                Button {
                    source: playersModel.iconsDir("gameicons/pairs2.png")
                    text: "Pairs 2"
                    onClicked: gameType = 'image2'
                }
                Button {
                    source: playersModel.iconsDir("gameicons/logic.png")
                    text: "Logic"
                    onClicked: gameType = 'logic'
                }
                Button {
                    source: playersModel.iconsDir("gameicons/sound.png")
                    text: "Sound"
                    onClicked: gameType = 'sound'
                }
                Button {
                    source: playersModel.iconsDir("gameicons/sound.png")
                    text: "SoundLogic"
                    onClicked: gameType = 'soundlogic'
                }
                Button {
                    source: playersModel.iconsDir("gameicons/words.png")
                    text: "Words"
                    onClicked: gameType = 'word'
                }
            }
            GridView {
                width: 400
                id: themesView
                height: parent.height
                model: themesModel
                
                MouseArea {
                    anchors.fill: parent
                    
                    onClicked: {
                        var idx=themesView.indexAt(mouse.x, mouse.y)
                        gameStarted()
                        fgame.newGame(idx, gameLanguage, gameType)
                    }
                }
                
                delegate: Column {
                    Image {
                        source: "image://theme/"+display+"/"+decoration
                        fillMode: Image.PreserveAspectFit
                        width: 100
                        height: 100
                    }
                    
                    Text {
                        width: 100
                        wrapMode: Text.WordWrap
                        font.pixelSize: 20
                        horizontalAlignment: Text.AlignHCenter
                        text: display
                    }
                }
            }
        }
    }
}