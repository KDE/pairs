/*  This file is part of Pairs
 *
 *  Copyright (C) <2008>       <Albert Astals Cid>   <aacid@kde.org>
 *  Copyright (C) <2011>       <Aleix Pol>           <aleixpol@kde.org>
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

#include "pairs.h"
#include "pairsview.h"
#include <QApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDebug>
#include "pairstheme.h"

static const char description[] =
    I18N_NOOP("A game to enhance your memory for KDE!");

static const char version[] = "2.0.0";

int main(int argc, char **argv)
{
    KAboutData about("pairs", i18n("pairs"), version, i18n(description),
                     KAboutLicense::LGPL, i18n("(C) 2011 Aleix Pol Gonzalez"));
    about.addAuthor( i18n("Aleix Pol Gonzalez"), i18n("Initial implementation and maintainer"), QStringLiteral("aleixpol@kde.org"), 0);
    about.addAuthor( i18n("Marco Calignano"), i18n("Theme support enhancement and general feature development"), QStringLiteral("marco.calignano@gmail.com"), 0);
    about.addAuthor( i18n("Albert Astals Cid"), i18n("Initial project setup and ideas"), QStringLiteral("aacid@kde.org"), 0);
    KCmdLineArgs::init(argc, argv, QByteArray("pairs"), QByteArray("pairs"), KLocalizedString(), QByteArray(version));
  
    KCmdLineOptions options;
    options.add("fullscreen", ki18n( "start in fullscreen mode"));
//    KCmdLineArgs::addCmdLineOptions(options);
    options.add("+[file]", ki18n("Pairs theme to open")); //new
    KCmdLineArgs::addCmdLineOptions(options); //new

    QApplication app(argc, argv);
    
    // see if we are starting with session management
    if (app.isSessionRestored())
    {
//TODO        RESTORE(Pairs);
    }
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        bool fsMode = KCmdLineArgs::parsedArgs()->isSet("fullscreen");
        Pairs *widget = 0;
        if(args->count())
        {
             widget = new Pairs(args->url(0).toLocalFile());
        }
        else
        {
            widget = new Pairs;
        }
    	args->clear();
//TODO
//        widget->view()->setLanguage(KSharedConfig::locale()->language().left(2));
        if (fsMode) 
        {
            widget->view()->showFullScreen();
        }
        else
        {
            widget->view()->show();
        }
    }
    return app.exec();
}
