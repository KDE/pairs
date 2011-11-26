import QtQuick 1.0

Rectangle {
    id: gameSettings
    property string gamelanguage;
    property string gametype;   
    gametype: 'image'
    gamelanguage: 'en'
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
                    source: "file://"+playersModel.iconsDir()+"gameicons/pairs.png"
                    text: "Pairs"
                    onClicked: {
                        gametype = 'image';
                        themesModel.refresh(gametype, gamelanguage)
                    }
                }
                Button {
                    source: "file://"+playersModel.iconsDir()+"gameicons/pairs2.png"
                    text: "Pairs 2"
                    onClicked: {
                        gametype = 'image2';
                        themesModel.refresh(gametype, gamelanguage)
                    }
                }
                Button {
                    source: "file://"+playersModel.iconsDir()+"gameicons/logic.png"
                    text: "Logic"
                    onClicked: {
                        gametype = 'logic';
                        themesModel.refresh(gametype, gamelanguage)
                    }
                }
                Button {
                    source: "file://"+playersModel.iconsDir()+"gameicons/sound.png"
                    text: "Sound"
                    onClicked: {
                        gametype = 'sound';
                        themesModel.refresh(gametype, gamelanguage)
                    }
                }
                Button {
                    source: "file://"+playersModel.iconsDir()+"gameicons/sound.png"
                    text: "SoundLogic"
                    onClicked: {
                        gametype = 'soundlogic';
                        themesModel.refresh(gametype, gamelanguage)
                    }
                }
                Button {
                    source: "file://"+playersModel.iconsDir()+"gameicons/words.png"
                    text: "Words"
                    onClicked: {
                        gametype = 'word';
                        themesModel.refresh(gametype, gamelanguage)
                    }
                }
            }
            GridView {
                width: 400
                id: themesView
                height: parent.height
                MouseArea {
                    anchors.fill: parent
                    
                    onClicked: {
                        var idx=themesView.indexAt(mouse.x, mouse.y)
                        gameStarted()
                        fgame.newGame(idx, gamelanguage, gametype)
                        playersModel.gameStarted();
                    }
                }
                model: themesModel
                delegate: Column {
                    Image { source: "image://theme/"+display+"/"+decoration; fillMode: Image.PreserveAspectFit; width: 100; height: 100 } 
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