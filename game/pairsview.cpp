/*  This file is part of Pairs
 *
 *  Copyright (C) <2008>       <Albert Astals Cid>   <aacid@kde.org>
 *  Copyright (C) <2010>       <Aleix Pol>           <aleixpol@kde.org>
 *  Copyright (C) <2011>       <Marco Calignano>     <marco.calignano@googlemail.com>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 2 of
 *  the License or (at your option) version 3 or any later version
 *  accepted by the membership of KDE e.V. (or its successor approved
 *  by the membership of KDE e.V.), which shall act as a proxy 
 *  defined in Section 14 of version 3 of the license.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pairsview.h"
#include "cardmodel.h"
#include "pairstheme.h"
#include "themesmodel.h"
#include "themeiconsprovider.h"
#include "pairsplayer.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QDate>
#include <QTimer>
#include <QFile>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QCoreApplication>
#include <QQmlContext>
// #ifndef QT_NO_OPENGL
//     #include <QGLWidget>
// #endif
#include "playersmodel.h"
#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>

#include <QStandardPaths>
#include <KNewStuff3/kns3/downloaddialog.h>
#include <KNewStuff3/kns3/entry.h>
#include <QResizeEvent>
#include <cmath>
#include <KRandom>
#include <KDeclarative/KDeclarative>
//#include <KStandardDirs>
//#include <kdeclarative.h>

PairsView::PairsView(const QString &file, QWindow *parent)
    : QQuickView(parent)
    , m_knsDialog(0)
{
    m_model = new ThemesModel(this, file);
    m_cards = new CardModel(this);
    m_players = new PlayersModel(this);
    m_themeImagesProvider = new ThemeIconsProvider(QQuickImageProvider::Pixmap, m_model);
    
    m_themeImagesProvider = new ThemeIconsProvider(QQuickImageProvider::Pixmap, m_model);

    rootContext()->setContextProperty("fgame", this);
    rootContext()->setContextProperty("themesModel", m_model);
    rootContext()->setContextProperty("playersModel", m_players);
    rootContext()->setContextProperty("cardModel", m_cards);
    engine()->addImageProvider("theme", m_themeImagesProvider);

    KDeclarative::KDeclarative kdeclarative;
    kdeclarative.setDeclarativeEngine(engine());
    kdeclarative.setupBindings();

    setSource(QUrl("qrc:/qml/Main.qml"));
    Q_ASSERT(errors().isEmpty());
    
    connect(engine(), SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));
    
    m_media = new Phonon::MediaObject(this);
    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::GameCategory, this);
    createPath(m_media, audioOutput);
}

PairsView::~PairsView()
{}

void PairsView::newGame(int row, const QString& cardType)
{
    PairsTheme* theme=static_cast<PairsTheme*>(m_model->item(row));
    newGame(theme, m_language, cardType);
}

void PairsView::newGame(const PairsTheme* theme, const QString& language, const QString& cardType)
{
    m_cards->clear();
    QQuickItem* cardsParent=findChild<QQuickItem*>("board");
    playersModel()->resetPlayers();
    Q_ASSERT(cardsParent);
    
    QList<ThemeElement> items = theme->items();
    //int num=qMin(((rows*columns)/2)*2, items.size()); //we make it %2
    int num = items.size();
    const CardType type = PairsTheme::cardNameToType(cardType);
    QByteArray file_buf;

    if(theme->backImage().isEmpty()){
        QString dir = QStandardPaths::locate(QStandardPaths::DataLocation, QLatin1String( "gameicons/pairs.svg"), QStandardPaths::LocateDirectory);
        QFile f(dir+"gameicons/pairsIcon.svg");
        f.open(QIODevice::ReadOnly);
        file_buf = f.readAll();
    }
    else{
        file_buf = (theme->themeData(theme->backImage()));
    }
    QImage backImage;
    backImage.loadFromData(file_buf);
    for(int i=0; i<num; i++) {
        ThemeElement titem = items.at(i);
        QString file = titem.value(theme->mainType(), language);
        QImage  frontImage;
        QString text;
        QByteArray fsound;
        QByteArray msound;
        CardType mtype = type;
        switch(type){
            case CARD_SOUNDLOGIC:
            	mtype = CARD_LOGIC;
            case CARD_SOUND:
            {
                QString dir = QStandardPaths::locate(QStandardPaths::DataLocation, QLatin1String( "gameicons/pairs.svg"), QStandardPaths::LocateDirectory);
                frontImage.load(dir+"gameicons/sound.svg");
                fsound = theme->themeData(file);
           }   break;
            case CARD_IMAGE2:
            case CARD_IMAGE:
            case CARD_LOGIC:
            	frontImage.loadFromData(theme->themeData(file));
                break;
            case CARD_WORD:
                text = file;
                break;
            default:
                break;
        }
        if(type == CARD_LOGIC || type == CARD_SOUNDLOGIC) {}
        m_cards->addCard(new CardItem(cardsParent, frontImage, backImage, text, "", fsound, msound, mtype, i));
        m_cards->addCard(new CardItem(cardsParent, frontImage, backImage, text, "", fsound, msound, mtype, i));
    }
}


void PairsView::download()
{
    if(!m_knsDialog)
        m_knsDialog=new KNS3::DownloadDialog("pairs.knsrc", 0);
    
    m_knsDialog->show();
}


/*
void PairsView::playSound(const QByteArray& sound) const
{
    QBuffer* b = new QBuffer;
    b->setData(sound);
    Phonon::MediaSource media(b);
    if(m_media->state()==Phonon::PlayingState) {
        m_media->setQueue(QList<Phonon::MediaSource>() << media);
    } else {
        m_media->setCurrentSource(media);
        m_media->play();
    }
    connect(m_media, SIGNAL(finished()), b, SLOT(deleteLater()));
}
*/
