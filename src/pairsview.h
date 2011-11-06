/*
 *  Copyright (C) <2007>       <Albert Astals Cid>   <aacid@kde.org>
 *  Copyright (C) <2010>       <Aleix Pol>           <aleixpol@kde.org>
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


#ifndef PAIRSVIEW_H
#define PAIRSVIEW_H

#include <QDeclarativeView>

namespace Phonon { class MediaObject;}

class ThemesModel;
class PairsTheme;
class CardItem;
class ThemeIconsProvider;
class PairsView : public QDeclarativeView
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    PairsView(QWidget *parent);

    /**
     * Destructor
     */
    virtual ~PairsView();
    
    void setRowSize(int itemsPerRow);
    int cardsNum();
    void newGame(const PairsTheme* theme, const QString& language, const QString& cardType);
    
    Q_SCRIPTABLE void newGame(int row, const QString& language, const QString& cardType);
signals:
    void pair_missed();
    void pair_found();
    
public slots:
    void download();
    void cardSelected(CardItem* cardData);
    
private:
    ThemesModel* m_model;
    CardItem* m_last;
    QList<CardItem*> m_cards;
    QSizeF m_cardsSize;
    ThemeIconsProvider *m_themeImagesProvider;
};

#endif // kpairsVIEW_H
