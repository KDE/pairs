/*
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
#include <QDebug>
#include <QPropertyAnimation>
#include <QGraphicsRotation>
#include <QDate>
#include <QTimer>
#include <QSvgRenderer>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDeclarativeItem>
#include <QDeclarativeContext>
#include <KTar>
#include <Phonon/MediaObject>
#include "pairstheme.h"
#include "themesmodel.h"
#include "themeiconsprovider.h"
#include "playersmodel.h"

#include <knewstuff3/downloaddialog.h>
#include <knewstuff3/entry.h>
#include "pairsplayer.h"

PairsView::PairsView(QWidget *parent)
    : QDeclarativeView(parent)
    , m_last(0)
    , m_cardsSize(128,128)
    , m_knsDialog(0)
    , m_players(new PlayersModel(this))
{
    m_model = new ThemesModel(this);
    m_themeImagesProvider = new ThemeIconsProvider(QDeclarativeImageProvider::Pixmap, m_model);
    
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    
    QObject::connect(this, SIGNAL(pair_missed()), parent, SLOT(inc_missed()));
    QObject::connect(this, SIGNAL(pair_found()), parent, SLOT(inc_found()));
    
    qsrand(QTime::currentTime().msec()*QTime::currentTime().second());
    
//     qmlRegisterType<ThemesModel>("org.kde.edu.pairs", 1, 0, "ThemesModel");
    
    setResizeMode(SizeRootObjectToView);
    
    rootContext()->setContextProperty("fgame", this);
    rootContext()->setContextProperty("themesModel", m_model);
    rootContext()->setContextProperty("playersModel", m_players);
    engine()->addImageProvider("theme", m_themeImagesProvider);

    setSource(QUrl("qrc:/qml/Main.qml"));
    Q_ASSERT(errors().isEmpty());
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
            emit pair_found();
            m_players->player(m_currentPlayer)->incFound();
            QTimer::singleShot(500, this, SLOT(checkGameOver()));
        } else {
            QTimer::singleShot(500, card, SLOT(turn()));
            QTimer::singleShot(500, m_last, SLOT(turn()));
            emit pair_missed();
            m_players->player(m_currentPlayer)->incMissed();
            ++m_currentPlayer %= m_players->rowCount();
        }
        m_last=0;
    }
    else {
        m_last=card;
    }
}

void PairsView::setRowSize(int itemsPerRow)
{
    int i=0;
    
    foreach(CardItem* card, m_cards) {
        QPointF p((i%itemsPerRow)*(m_cardsSize.width()+10), (i/itemsPerRow)*(m_cardsSize.height()+10));
        
        QPropertyAnimation* anim = new QPropertyAnimation(card, "position", card);
        anim->setEndValue(p);
        anim->setDuration(1000);
        
        anim->start(QAbstractAnimation::DeleteWhenStopped);
        i++;
    }
}

void PairsView::newGame(int row, const QString& language, const QString& cardType)
{
    PairsTheme* theme=static_cast<PairsTheme*>(m_model->item(row));
    newGame(theme, language, cardType);
}

void PairsView::newGame(const PairsTheme* theme, const QString& language, const QString& cardType)
{
    qDeleteAll(m_cards);
    m_cards.clear();
    QList<CardItem*> cards;
    KTar archive(theme->path());
    bool b = archive.open(QIODevice::ReadOnly);
    Q_ASSERT(b && "could not open the file");
    
    QDeclarativeItem* cardsParent=rootObject()->findChild<QDeclarativeItem*>("board");
    
    Q_ASSERT(cardsParent);
    
    QList<ThemeElement> items = theme->items();
    //int num=qMin(((rows*columns)/2)*2, items.size()); //we make it %2
    int num = items.size();
    QSvgRenderer backRenderer(static_cast<const KArchiveFile*>(archive.directory()->entry(theme->backImage()))->data());
    for(int i=0; i<num; i++) {
        ThemeElement titem = items.at(i);

//         qDebug() << theme.mainType() << titem.name[1] << titem.name[2] << titem.name[3] << titem.name[4] << titem.name[5];

        CardItem* item = new CardItem(&backRenderer, m_cardsSize, cardsParent, scene());
        item->setData(0, i);
        item->setType(theme->mainType(), titem.name[theme->mainType()][language], archive);

        CardItem* item1 = new CardItem(&backRenderer, m_cardsSize, cardsParent, scene());
        item1->setData(0, i);
        //for now  fixed to test sound
        CardType type = CARD_IMAGE;
        if(cardType == "image") type = CARD_IMAGE;
        else if(cardType == "sound") type = CARD_SOUND;
        else if(cardType == "video") type = CARD_VIDEO;
        else if(cardType == "word") type = CARD_WORD;
        item1->setType(type, titem.name[type][language], archive);

        connect(item,  SIGNAL(selected(CardItem*)), SLOT(cardSelected(CardItem*)));
        connect(item1, SIGNAL(selected(CardItem*)), SLOT(cardSelected(CardItem*)));
        cards += item;
        cards += item1;

    }
    
    while(!cards.isEmpty())
        m_cards += cards.takeAt(qrand()%cards.size());
    
    if(num % 2 == 0)
    	setRowSize(qMax(4, num/2));
    else
    	setRowSize((2*num)/3);
    
    
    QObject* cardsContext=rootObject()->findChild<QObject*>("board");
    Q_ASSERT(cardsContext);
    cardsContext->setProperty("isGameOver", QVariant(false));

    m_currentPlayer=0;
    m_timer->start(1000);
}

void PairsView::checkGameOver()
{
    if(isGameOver()) {
        QObject* cardsContext=rootObject()->findChild<QObject*>("board");
        Q_ASSERT(cardsContext);
        cardsContext->setProperty("isGameOver", true);
        m_timer->stop();
    }
}

void PairsView::download()
{
    if(!m_knsDialog)
        m_knsDialog=new KNS3::DownloadDialog("pairs.knsrc", this);
    
    m_knsDialog->show();
}


#include "pairsview.moc"
