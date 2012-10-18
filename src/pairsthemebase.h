/*  This file is part of Pairs
 *
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

#ifndef PAIRSTHEMEBASE_H
#define PAIRSTHEMEBASE_H
#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtCore/QSet>
#include <QtGui/QStandardItem>
#include "cardtype.h"
#include <QtXml/QXmlStreamReader>

class ThemeElement {
public:
    QMap<QString, QString>  name[CARD_MAX_TYPE];
    QMap<QString, QString> found;
    ThemeElement(){ reset(); };
    
    void reset() {
        for(int i = 0; i < CARD_MAX_TYPE; i++) name[i].clear();
        found.clear();
    };
    
    QString value(CardType type, const QString& language) const;
    QStringList langlist(CardType type) const;
    QStringList foundLanglist() const;
    QString foundSound(const QString& lang) const;
};

class PairsThemeBase : public QObject, public QStandardItem
{
    Q_OBJECT

    public:
        enum ThemeRoles {
             CardTypeRole = Qt::UserRole + 1,
             LanguagesRole,
             PathRole
         };

        PairsThemeBase();
        bool isPertinent(const QString &type,const QString &lang);
        static CardType cardNameToType(const QString& name);
        QString title() const { return m_title; }
        void setTitle(const QString &title) {m_title = title; setText(title);}
        QString description() const { return m_description; }
        QString backImage() const { return m_back_img; }
        QList<ThemeElement> items() const { return m_items; }
        bool isCorrect() const { return m_error.isEmpty(); }
        QString error() const { return m_error; }
        CardType mainType() const { return m_main_type; }
        QString author() const { return m_author; }
        QString version() const { return m_version; }
        QString date() const { return m_date; }

        virtual QStringList images() const = 0;
        virtual bool hasFile(const QString& path) const = 0;
        virtual QString path() const = 0;
        
    protected:
        void parse(QXmlStreamReader &reader);
        void parseElement(QXmlStreamReader &reader);

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
        QSet<QString> m_languages;
        QMap<QString, QSet<QString> > m_cardtypes;

};

#endif // PAIRSTHEMEBASE_H
