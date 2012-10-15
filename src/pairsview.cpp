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
#include "carditem.h"
#include "pairstheme.h"
#include "themesmodel.h"
#include "themeiconsprovider.h"
#include "playersmodel.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QGraphicsRotation>
#include <QDate>
#include <QTimer>
#include <QFile>
#include <QSvgRenderer>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeItem>
#include <QCoreApplication>
#include <QDeclarativeContext>
// #ifndef QT_NO_OPENGL
//     #include <QGLWidget>
// #endif
#include <Phonon/MediaObject>
#include <Phonon/AudioOutput>

#include <knewstuff3/downloaddialog.h>
#include <knewstuff3/entry.h>
#include <QResizeEvent>
#include <cmath>
#include <KRandom>
#include <KStandardDirs>
#include <kdeclarative.h>
#include "pairsplayer.h"

PairsView::PairsView(QWidget *parent)
    : QDeclarativeView(parent)
    , m_last(0)
    , m_knsDialog(0)
    , m_itemsPerRow(1)
{
// #ifndef QT_NO_OPENGL
//     setViewport(new QGLWidget);
// #endif
    
    m_model = new ThemesModel(this);
    m_players = new PlayersModel(this);
    m_themeImagesProvider = new ThemeIconsProvider(QDeclarativeImageProvider::Pixmap, m_model);
    
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    
    connect(m_players, SIGNAL(rowsRemoved(QModelIndex,int,int)), m_timer, SLOT(stop()));
//     qmlRegisterType<ThemesModel>("org.kde.edu.pairs", 1, 0, "ThemesModel");
    
    setResizeMode(SizeRootObjectToView);
    
    rootContext()->setContextProperty("fgame", this);
    rootContext()->setContextProperty("themesModel", m_model);
    rootContext()->setContextProperty("playersModel", m_players);
    engine()->addImageProvider("theme", m_themeImagesProvider);


    KDeclarative m_kdeclarative;
    m_kdeclarative.setDeclarativeEngine(engine());
    m_kdeclarative.initialize();
    //binds things like kconfig and icons
    m_kdeclarative.setupBindings();


    setSource(QUrl("qrc:/qml/Main.qml"));
    Q_ASSERT(errors().isEmpty());
    
    m_resizeTimer = new QTimer(this);
    m_resizeTimer->setSingleShot(true);
    connect(m_resizeTimer, SIGNAL(timeout()), SLOT(reorganizeCards()));
    connect(engine(), SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));
    
    m_media = new Phonon::MediaObject(this);
    Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput(Phonon::GameCategory, this);
    createPath(m_media, audioOutput);
}

PairsView::~PairsView()
{}

int PairsView::cardsNum()
{
   return m_cards.count();
}

bool PairsView::isGameOver() const
{
    foreach(CardItem* card, m_cards) {
        if(!card->isDone())
            return false;
    }
    return true;
}

void PairsView::update()
{
    m_players->player(m_currentPlayer)->incSeconds();
}

void PairsView::cardSelected(CardItem* card)
{
    Q_ASSERT(card);
    
    if(m_last) {
        if(m_last->data(0)==card->data(0)) {
            m_last->markDone();
            card->markDone();
            playSound(card->foundSound());
            m_players->player(m_currentPlayer)->incFound();
            QTimer::singleShot(500, this, SLOT(checkGameOver()));
        } else {
            connect(m_media, SIGNAL(finished()), card, SLOT(turn()));
            connect(m_media, SIGNAL(finished()), m_last, SLOT(turn()));
            playSound(card->missedSound());
            m_players->player(m_currentPlayer)->incMissed();
            
            //next player
            do {
                ++m_currentPlayer %= m_players->rowCount();
            } while(!m_players->player(m_currentPlayer)->isSelected());
            emit currentPlayerChanged();
        }
        m_last=0;
    }
    else {
        m_last=card;
    }
}

void PairsView::newGame(int row, const QString& cardType)
{
    PairsTheme* theme=static_cast<PairsTheme*>(m_model->item(row));
    newGame(theme, m_language, cardType);
}

void PairsView::newGame(const PairsTheme* theme, const QString& language, const QString& cardType)
{
    qDeleteAll(m_cards);
    m_last = 0;
    m_cards.clear();
    QList<CardItem*> cards;
    
    QDeclarativeItem* cardsParent=rootObject()->findChild<QDeclarativeItem*>("board");
    playersModel()->resetPlayers();
    Q_ASSERT(cardsParent);
    
    QList<ThemeElement> items = theme->items();
    //int num=qMin(((rows*columns)/2)*2, items.size()); //we make it %2
    int num = items.size();
    const CardType type = PairsTheme::cardNameToType(cardType);
    QByteArray file_buf;

    if(theme->backImage().isEmpty()){
        QString dir = KGlobal::dirs()->findResourceDir("appdata", QLatin1String( "gameicons/pairs.svg"));
        QFile f(dir+"gameicons/pairsIcon.svg");
        f.open(QIODevice::ReadOnly);
        file_buf = f.readAll();
    }
    else{
        file_buf = (theme->themeData(theme->backImage()));
    }
    QSharedPointer<QSvgRenderer> backRenderer(new QSvgRenderer(file_buf));
    for(int i=0; i<num; i++) {
        ThemeElement titem = items.at(i);

        CardItem* item = new CardItem(backRenderer, cardsParent, scene(), m_media);
        item->setData(0, i);
        if(type == CARD_LOGIC || type == CARD_SOUNDLOGIC) {
            item->setType(CARD_LOGIC, titem.value(theme->mainType(), language), theme);
        } else {
            item->setType(theme->mainType(), titem.value(theme->mainType(), language), theme);
        }

        CardItem* item1 = new CardItem(backRenderer, cardsParent, scene(), m_media);
        item1->setData(0, i);

//         qDebug() << cardType << titem.name[type][language];

        item1->setType(type, titem.value(type, language), theme);
        if(type == CARD_LOGIC || type == CARD_SOUNDLOGIC) {
            item->setDuration(0);
            item1->setDuration(0);
        }

        item->setFoundSound(theme->themeData(titem.foundSound(language)));
        item1->setFoundSound(theme->themeData(titem.foundSound(language)));
        connect(item,  SIGNAL(selected(CardItem*)), SLOT(cardSelected(CardItem*)));
        connect(item1, SIGNAL(selected(CardItem*)), SLOT(cardSelected(CardItem*)));
        cards += item;
        cards += item1;

    }
    
    while(!cards.isEmpty())
        m_cards += cards.takeAt(KRandom::random()%cards.size());
    
    if(num % 2 == 0)
    	setRowSize(qMax(4, num/2));
    else
    	setRowSize((2*num)/3);
    
    
    QObject* cardsContext=rootObject()->findChild<QObject*>("board");
    Q_ASSERT(cardsContext);
    cardsContext->setProperty("isGameOver", QVariant(false));

    m_currentPlayer=-1;
    for(int i=0; i<m_players->rowCount(); i++) {
        if(m_players->player(i)->isSelected()) {
            m_currentPlayer = i;
            break;
        }
    }
    emit currentPlayerChanged();
    
    Q_ASSERT(m_currentPlayer>=0 && "some player must be selected first");
    m_timer->start(1000);
}

void PairsView::checkGameOver()
{
    if(isGameOver()) {
        QObject* cardsContext=rootObject()->findChild<QObject*>("board");
        Q_ASSERT(cardsContext);
        cardsContext->setProperty("isGameOver", true);
        stopGame();
    }
}

void PairsView::stopGame()
{
    m_timer->stop();
}

void PairsView::download()
{
    if(!m_knsDialog)
        m_knsDialog=new KNS3::DownloadDialog("pairs.knsrc", this);
    
    m_knsDialog->show();
}

void PairsView::resizeEvent(QResizeEvent* ev)
{
    QDeclarativeView::resizeEvent(ev);
    
    m_resizeTimer->start(100);
}

void PairsView::setRowSize(int itemsPerRow)
{
    m_itemsPerRow = itemsPerRow;
    
    reorganizeCards(true);
}

void PairsView::reorganizeCards(bool starting)
{
    QDeclarativeItem* cardsParent=rootObject()->findChild<QDeclarativeItem*>("board");
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
