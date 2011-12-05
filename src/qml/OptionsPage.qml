import QtQuick 1.0

Page {
    id: gameSettings
    property string gameLanguage: 'en'
    property string gameType: 'image'
    
    signal gameStarted;
    
    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 50
        Flow {
            width: parent.width
            spacing: 20
            Button {
                source: playersModel.iconsDir("gameicons/pairs.png")
                text: qsTr("Pairs")
                onClicked: gameType = 'image'
            }
            Button {
                source: playersModel.iconsDir("gameicons/pairs2.png")
                text: qsTr("Similar")
                onClicked: gameType = 'image2'
            }
            Button {
                source: playersModel.iconsDir("gameicons/logic.png")
                text: qsTr("Logic")
                onClicked: gameType = 'logic'
            }
            Button {
                source: playersModel.iconsDir("gameicons/sound.png")
                text: qsTr("Sound")
                onClicked: gameType = 'sound'
            }
            Button {
                source: playersModel.iconsDir("gameicons/sound.png")
                text: qsTr("SoundLogic")
                onClicked: gameType = 'soundlogic'
            }
            Button {
                source: playersModel.iconsDir("gameicons/words.png")
                text: qsTr("Words")
                onClicked: gameType = 'word'
            }
        }
        
        Flow {
            id: themesView
            width: parent.width
            spacing: 20
            
            Repeater {
                model: themesModel
                
                delegate: Button {
                    visible: themesModel.isPertinent(index, gameType, gameLanguage)
                    source: "image://theme/"+display+"/"+decoration
                    text: display
                    font.pointSize: 12
                    
                    onClicked: {
                        gameStarted()
                        fgame.newGame(index, gameLanguage, gameType)
                    }
                }
            }
        }
    }
}