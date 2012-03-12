import QtQuick 1.0

Page {
    id: gameSettings
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
                text: i18n("Pairs")
                onClicked: gameType = 'image'
            }
            Button {
                source: playersModel.iconsDir("gameicons/pairs2.png")
                text: i18n("Similar")
                onClicked: gameType = 'image2'
            }
            Button {
                source: playersModel.iconsDir("gameicons/logic.png")
                text: i18n("Logic")
                onClicked: gameType = 'logic'
            }
            Button {
                source: playersModel.iconsDir("gameicons/sound.png")
                text: i18n("Sound")
                onClicked: gameType = 'sound'
            }
            Button {
                source: playersModel.iconsDir("gameicons/sound.png")
                text: i18n("SoundLogic")
                onClicked: gameType = 'soundlogic'
            }
            Button {
                source: playersModel.iconsDir("gameicons/words.png")
                text: i18n("Words")
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
                    visible: themesModel.isPertinent(index, gameType, fgame.language())
                    source: "image://theme/"+display+"/"+decoration
                    text: display
                    font.pointSize: 12
                    
                    onClicked: {
                        if(!playersModel.isAnySelected()) {
                            //if there are no selected players, select the first one
                            //if there's none, just create one
                            if(playersModel.count>0)
                                playersModel.toggleSelection(0)
                            else
                                addPlayer()
                        }
                        
                        gameStarted()
                        fgame.newGame(index, gameType)
                    }
                }
            }
        }
    }
}