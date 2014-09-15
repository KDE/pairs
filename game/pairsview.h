/*  This file is part of Pairs
 *
 *  Copyright (C) <2007>       <Albert Astals Cid>   <aacid@kde.org>
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


#ifndef PAIRSVIEW_H
#define PAIRSVIEW_H

#include <QQuickView>


namespace KNS3 { class DownloadDialog; }
namespace Phonon { class MediaObject;}

class PlayersModel;
class ThemesModel;
class PairsTheme;
class CardModel;
class QQmlEngine;
class ThemeIconsProvider;
class PairsView : public QQuickView
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    PairsView(QQmlEngine *pengine, const QString &file = "", QWindow *parent = 0);

    /**
     * Destructor
     */
    virtual ~PairsView();
    
    PlayersModel* playersModel() const { return m_players; }
    void setLanguage(const QString &l) { m_language = l; }
    int currentPlayer() const { return m_currentPlayer; }
    
    Q_SCRIPTABLE void newGame(int row, const QString& cardType);
    Q_SCRIPTABLE QString language(){return m_language;};
public slots:
    void download();

private:
    void newGame(const PairsTheme* theme, const QString& language, const QString& cardType);
//    void playSound(const QByteArray& sound) const;
    ThemesModel* m_model;
    CardModel* m_cards;
    ThemeIconsProvider *m_themeImagesProvider;
    KNS3::DownloadDialog *m_knsDialog;
    PlayersModel* m_players;
    int m_currentPlayer;
    QString m_language;
    Phonon::MediaObject *m_media;
};

#endif // kpairsVIEW_H
