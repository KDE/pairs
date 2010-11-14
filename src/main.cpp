#include "kmemory.h"
#include <KDE/KApplication>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KLocale>

static const char description[] =
    I18N_NOOP("A KDE 4 Application");

static const char version[] = "0.1";

int main(int argc, char **argv)
{
    KAboutData about("kmemory", 0, ki18n("kmemory"), version, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2007 Albert Astals Cid"), KLocalizedString(), 0, "aacid@kde.org");
    about.addAuthor( ki18n("Albert Astals Cid"), KLocalizedString(), "aacid@kde.org" );
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    options.add("+[URL]", ki18n( "Document to open" ));
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    kmemory *widget = new kmemory;

    // see if we are starting with session management
    if (app.isSessionRestored())
    {
        RESTORE(kmemory);
    }
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        if (args->count() == 0)
        {
            //kmemory *widget = new kmemory;
            widget->show();
        }
        else
        {
            int i = 0;
            for (; i < args->count(); i++)
            {
                //kmemory *widget = new kmemory;
                widget->show();
            }
        }
        args->clear();
    }

    return app.exec();
}
