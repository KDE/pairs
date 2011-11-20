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
            SelectableListView {
                width: 200
                id: themesView
                height: parent.height
                
                onCurrentItemChanged: {
                    languagesView.model=themesModel.info(currentIndex, 'languages')
                    typesView.model=themesModel.info(currentIndex, 'type')
                }
                Grid {
                    columns: 4
                    spacing: 20         
                    Repeater {
                        model: themesModel
                        delegate: Column {
                            Image { source: "image://theme/"+display+"/"+decoration; fillMode: Image.PreserveAspectFit; height: 100 } 
                            Text {
                                font.pixelSize: 25 
                                text: display
                            }
                        }
                    }
                }    
            }
        }
                
        Column {
            Button {
                text: "New Game!"
                
                onClicked: {
                    gameStarted()
                    fgame.newGame(themesView.currentIndex, languagesView.currentItem.text, typesView.currentItem.text)
                }
            }
            
            Button {
                text: "Download Themes"
                
                onClicked: fgame.download()
            }
        }
    }
}