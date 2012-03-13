/*
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
#include <KDE/KApplication>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KLocale>
#include <KStandardDirs>
#include <QDebug>
#include "pairstheme.h"

static const char description[] =
    I18N_NOOP("A game to enhance your memory for KDE!");

static const char version[] = "0.2";

int main(int argc, char **argv)
{
    KAboutData about("pairs", 0, ki18n("pairs"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2011 Aleix Pol Gonzalez"), KLocalizedString(), 0, "aleixpol@kde.org");
    about.addAuthor( ki18n("Aleix Pol Gonzalez"), ki18n("Initial implementation and maintainer"), "aleixpol@kde.org" );
    about.addAuthor( ki18n("Marco Calignano"), ki18n("Theme support enhancement and general feature development"), "marco.calignano@googlemail.com");
    about.addAuthor( ki18n("Albert Astals Cid"), ki18n("Initial project setup and ideas"), "aacid@kde.org" );
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    options.add("fullscreen", ki18n( "start in fullscreen mode"));
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;
    
    // see if we are starting with session management
    if (app.isSessionRestored())
    {
        RESTORE(Pairs);
    }
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        bool fsMode = KCmdLineArgs::parsedArgs()->isSet("fullscreen");
        args->clear();
        Pairs *widget = new Pairs;

        if (fsMode) 
        {
            widget->showFullScreen();
        }
        else
        {
            widget->show();
        }
    }
    return app.exec();
}
