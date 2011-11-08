/*
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

#ifndef PAIRSTHEME_H
#define PAIRSTHEME_H
#include <QString>
#include <QMap>
#include <QVariant>
#include <QList>
#include <KTar>
#include <QXmlStreamReader>
#include <QStandardItem>
#include "cardtype.h"

class ThemeElement {
public:
    QMap<QString, QString>  name[CARD_MAX_TYPE];
    ThemeElement(){ reset(); };
    ~ThemeElement(){};
    void reset() {
        for(int i = 0; i < CARD_MAX_TYPE; i++) name[i].clear();
    };

};

class PairsTheme : public QObject, public QStandardItem
{
    Q_OBJECT

    public:
        enum ThemeRoles {
             CardTypeRole = Qt::UserRole + 1,
             LanguagesRole
         };

        PairsTheme(const QString& path);

        Q_PROPERTY(QString language READ mainLanguage WRITE setLanguage NOTIFY languageChanged);

        QString mainLanguage() const { return m_mainLanguage;}
        void setLanguage(QString &lang);
        QString title() const { return m_title; }
        QString description() const { return m_description; }
        QString backImage() const { return m_back_img; }
        QString path() const { return m_path; }
        
        QList<ThemeElement> items() const { return m_items; }
        
        bool isCorrect() const { return m_error.isEmpty(); }
        QString error() const { return m_error; }
        CardType mainType() const { return m_main_type; }
        QStringList images() const;
    signals:
        void languageChanged();
    private:
        void parseElement(QXmlStreamReader &reader);

        bool isValid(const KArchiveFile* file);
        QString m_data;
        QString m_title;
        QString m_description;
        QString m_author;
        QString m_date;
        QString m_version;

        QString m_missed_snd;
        QString m_found_snd;
        QString m_turn_snd;

        QString m_back_img;
        QString m_background_img;
        QString m_backtrasp_img;
        QString m_main;
        CardType m_main_type;

        QList<ThemeElement> m_items;
        
        QString m_error;
        QString m_path;
        QString m_mainLanguage;
        QStringList m_languages;
        QMap<QString, QStringList> m_cardtypes;
};

#endif // PAIRSTHEME_H
