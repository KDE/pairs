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
//#include <KStandardDirs>
//#include <kdeclarative.h>

PairsView::PairsView(QWindow *parent, QQmlEngine *pengine, const QString &file)
    : QQuickView(pengine, parent)
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

/* TODO
    KDeclarative m_kdeclarative;
    m_kdeclarative.setDeclarativeEngine(engine());
    m_kdeclarative.initialize();
    //binds things like kconfig and icons
    m_kdeclarative.setupBindings();

*/
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
<<<<<<< Updated upstream
    qDeleteAll(m_cards);
    m_last = 0;
    m_cards.clear();
    QList<CardItem*> cards;
    
    QQuickItem* cardsParent=findChild<QQuickItem*>("board");
=======
    m_cards->clear();
    QQuickItem* cardsParent=findChild<QQuickItem*>("board");
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream

        CardItem* item = new CardItem(backRenderer, cardsParent, m_media);
        item->setData(0, i);
        if(type == CARD_LOGIC || type == CARD_SOUNDLOGIC) {
            item->setType(CARD_LOGIC, titem.value(theme->mainType(), language), theme);
        } else {
            item->setType(theme->mainType(), titem.value(theme->mainType(), language), theme);
=======
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
>>>>>>> Stashed changes
        }
        if(type == CARD_LOGIC || type == CARD_SOUNDLOGIC) {}
        m_cards->addCard(new CardItem(cardsParent, frontImage, backImage, text, "", fsound, msound, mtype, i));
        m_cards->addCard(new CardItem(cardsParent, frontImage, backImage, text, "", fsound, msound, mtype, i));
    }
}

<<<<<<< Updated upstream
void PairsView::checkGameOver()
{
    if(isGameOver()) {
        QObject* cardsContext=findChild<QObject*>("board");
        Q_ASSERT(cardsContext);
        cardsContext->setProperty("isGameOver", true);
        stopGame();
    }
}

void PairsView::stopGame()
{
    m_timer->stop();
}
=======
>>>>>>> Stashed changes

void PairsView::download()
{
    if(!m_knsDialog)
        m_knsDialog=new KNS3::DownloadDialog("pairs.knsrc", 0);
    
    m_knsDialog->show();
}

<<<<<<< Updated upstream
void PairsView::resizeEvent(QResizeEvent* ev)
{
    QQuickView::resizeEvent(ev);
    
    m_resizeTimer->start(100);
}

void PairsView::setRowSize(int itemsPerRow)
{
    m_itemsPerRow = itemsPerRow;
    
    reorganizeCards(true);
}

void PairsView::reorganizeCards(bool starting)
{
    QQuickItem* cardsParent=findChild<QQuickItem*>("board");
    QSizeF s(cardsParent->width(), cardsParent->height());
    
    Q_ASSERT(m_itemsPerRow>0);
    
    int i=0;
    qreal rowCount = std::ceil(double(m_cards.size())/m_itemsPerRow);
    int minspacing = 5;
    qreal side = qMin((s.width()-m_itemsPerRow*minspacing)/m_itemsPerRow, (s.height()-rowCount*minspacing)/rowCount);
    
    qreal hspacing=(s.width()-m_itemsPerRow*side)/m_itemsPerRow;
    qreal vspacing=(s.height()-rowCount*side)/rowCount;
    
    foreach(CardItem* card, m_cards) {
        card->setSize(QSizeF(side, side));
        QPointF p(hspacing/2+(i%m_itemsPerRow)*(side+hspacing), vspacing/2+(i/m_itemsPerRow)*(side+vspacing));
        
        QPropertyAnimation* anim = new QPropertyAnimation(card, "position", card);
        anim->setEndValue(p);
        anim->setDuration(starting ? 300 : 0);
        anim->setEasingCurve(QEasingCurve::InOutQuad);
        
        anim->start(QAbstractAnimation::DeleteWhenStopped);
        i++;
    }
}
=======

>>>>>>> Stashed changes

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
