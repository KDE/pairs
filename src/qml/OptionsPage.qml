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
            Text { text: "Themes:"; font.bold: true; font.pixelSize: 25 }

            Row {
                spacing: 20
                Button {
                    text: "Pairs"
                    onClicked: {
                        gametype = 'image';
                        themesModel.refresh(gametype, gamelanguage)
                    }
                }
                Button {
                    text: "Pairs 2"
                    onClicked: {
                        gametype = 'sec image';
                        themesModel.refresh(gametype, gamelanguage)
                    }
                }
                Button {
                    text: "Logic"
                    onClicked: {
                        gametype = 'logic';
                        themesModel.refresh(gametype, gamelanguage)
                    }
                }
                Button {
                    text: "Sound"
                    onClicked: {
                        gametype = 'sound';
                        themesModel.refresh(gametype, gamelanguage)
                    }
                }
                Button {
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