/*  This file is part of Pairs
 *
 *  Copyright (C) <2012>       <Heena Mahour>        <heena393@gmail.com>
 *  Copyright (C) <2012>       <Marco Calignano>     <marco.calignano@gmail.com>
 *
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

#include <KApplication>
#include "mainwindow.h"
#include <KAboutData>
#include <KCmdLineArgs>
#include <kurl.h>

int main(int argc, char *argv[])
{
    KAboutData aboutData( "pairseditor", QByteArray(), ki18n("Pairs Editor"), "1.0",
                          ki18n("Pairs Themes Editor"), KAboutData::License_GPL,
                          ki18n("Copyright (c) 2012 the Pairs developers"));

    aboutData.addAuthor( ki18n("Aleix Pol Gonzalez"), ki18n("Maintainer"), "aleixpol@kde.org" );
    aboutData.addAuthor( ki18n("Marco Calignano"), ki18n("Feature development"), "marco.calignano@gmail.com");
    aboutData.addAuthor(ki18n("Heena Mahour"), ki18n("Layout development"), "heena393@gmail.com");
    KCmdLineArgs::init(argc, argv, &aboutData);
    KCmdLineOptions options;
    options.add("+[URL]", ki18n("Theme to open"));
    KCmdLineArgs::addCmdLineOptions( options );
    
    KApplication app;
    if (app.isSessionRestored())
    {
        RESTORE(MainWindow);
    } else {
        KCmdLineArgs* args = KCmdLineArgs::parsedArgs();
        
        // no session.. just start up normally
        MainWindow *w = new MainWindow;

        if(args->count()==2)
            w->open(args->url(0).toLocalFile());
        args->clear();
        w->show();
    }
    
    return app.exec();
}
