import QtQuick 1.0

Rectangle {
    id: gameSettings
    property string gameLanguage: 'en'
    property string gameType: 'image'
    
    color: 'green'
    signal gameStarted;
    
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
            
            Flow {
                id: themesView
                height: parent.height
                width: parent.width
                
                Repeater {
                    model: themesModel
                    
                    delegate: Button {
                        visible: themesModel.isPertinent(index, gameType, gameLanguage)
                        source: "image://theme/"+display+"/"+decoration
                        text: display
                        
                        onClicked: {
                            gameStarted()
                            fgame.newGame(index, gameLanguage, gameType)
                        }
                    }
                }
            }
        }
    }
}