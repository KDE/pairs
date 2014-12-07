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
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDebug>
#include <QCommandLineParser>
#include <QUrl>
#include <QDir>
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

    QApplication app(argc, argv);
    
    QCommandLineParser parser;
    KAboutData::setApplicationData(about);
    parser.addVersionOption();
    parser.addHelpOption();
    QCommandLineOption fullscreenOption("fullscreen", ki18n( "start in fullscreen mode").toString());
    parser.addOption(fullscreenOption);
    parser.addPositionalArgument("file", ki18n("Pairs theme to open").toString());
    about.setupCommandLine(&parser);
    parser.process(app);
    about.processCommandLine(&parser);

    // see if we are starting with session management
    if (app.isSessionRestored())
    {
//TODO        RESTORE(Pairs);
    }
    else
    {
        // no session.. just start up normally
        const QStringList args = parser.positionalArguments();
        bool fsMode = parser.isSet("fullscreen");
        Pairs *widget = 0;
        if(args.count())
        {
            QUrl url;
#if QT_VERSION >= 0x050400
            url = QUrl::fromUserInput(args[0], QDir::currentPath(), QUrl::AssumeLocalFile);
#else
            // Logic from QUrl::fromUserInput(QString, QString, UserInputResolutionOptions)
            url = (QUrl(args[0], QUrl::TolerantMode).isRelative() && !QDir::isAbsolutePath(args[0]))
                   ? QUrl::fromLocalFile(QDir::current().absoluteFilePath(args[0]))
                   : QUrl::fromUserInput(args[0]);
#endif
            widget = new Pairs(url.toLocalFile());
        }
        else
        {
            widget = new Pairs;
        }
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
