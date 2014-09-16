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


#include "mainwindow.h"
#include <KAboutData>

#include <kurl.h>
#include <QApplication>
#include <KLocalizedString>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[])
{
    KAboutData aboutData( "pairseditor", i18n("Pairs Editor"), "1.0.0",
                          i18n("Pairs Themes Editor"), KAboutLicense::GPL,
                          i18n("Copyright (c) 2012 the Pairs developers"));

    aboutData.addAuthor( i18n("Aleix Pol Gonzalez"), i18n("Maintainer"), "aleixpol@kde.org", 0);
    aboutData.addAuthor( i18n("Marco Calignano"), i18n("Feature development"), "marco.calignano@gmail.com", 0);
    aboutData.addAuthor( i18n("Heena Mahour"), i18n("Layout development"), "heena393@gmail.com", 0);
    aboutData.addAuthor( i18n("Ian Sanders"), i18n("Application icon development"), "iansan565@gmail.com", 0);
    QApplication app(argc, argv);
    QCommandLineParser parser;
    KAboutData::setApplicationData(aboutData);
    parser.addVersionOption();
    parser.addHelpOption();
    //PORTING SCRIPT: adapt aboutdata variable if necessary
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);
    parser.addOption(QCommandLineOption(QStringList() <<  QLatin1String("+[URL]"), i18n("Theme to open")));
    
    if (app.isSessionRestored())
    {
        RESTORE(MainWindow);
    } else {
        
        // no session.. just start up normally
        MainWindow *w = new MainWindow;

        if(parser.positionalArguments().count()==2)
            w->openfile(QUrl::fromUserInput(argv[1]).toLocalFile());
        
        w->show();
    }
    
    return app.exec();
}
