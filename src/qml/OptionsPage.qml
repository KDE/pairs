import QtQuick 1.0

Rectangle {
    color: 'green'
    signal gameStarted;
    
//     ListModel {
//         id: themesModel
//         ListElement { display: "a"; languages: "a"; type: "a" }
//         ListElement { display: "a"; languages: "a"; type: "a" }
//         ListElement { display: "a"; languages: "a"; type: "a" }
//         ListElement { display: "a"; languages: "a"; type: "a" }
//         ListElement { display: "a"; languages: "a"; type: "a" }
//         ListElement { display: "a"; languages: "a"; type: "a" }
//     }
    
    Row {
        anchors.margins: 30
        anchors.fill: parent
        
        Column {
            height: parent.height
            Text { text: "Themes:"; font.bold: true; font.pixelSize: 25 }
            
            SelectableListView {
                width: 200
                id: themesView
                height: parent.height
                
                onCurrentItemChanged: {
                    languagesView.model=themesModel.info(currentIndex, 'languages')
                    typesView.model=themesModel.info(currentIndex, 'type')
                }
                
                model: themesModel
                delegate: Row {
                    Image { source: "image://theme/"+display; fillMode: Image.PreserveAspectFit; height: 20 } 
                    Text {
                        font.pixelSize: 25 
                        
                        text: display
                    }
                }
            }
        }
        
        Column {
            height: parent.height
            Text { text: "Languages:"; font.bold: true; font.pixelSize: 25 }
            
            SelectableListView {
                id: languagesView
                width: 200
                height: parent.height
                
                delegate: Text { text: modelData; font.pixelSize: 25  }
            }
        }
        
        Column {
            height: parent.height
            Text { text: "Game Types:"; font.bold: true; font.pixelSize: 25 }
            
            SelectableListView {
                id: typesView
                width: 200
                height: parent.height
                
                delegate: Text { text: modelData; font.pixelSize: 25  }
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