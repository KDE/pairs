#include "ptedit.h"

#include <KDE/KApplication>
#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>

static const char version[] = "0.1";


int main(int argc, char *argv[])
{
    KAboutData about("ptedit", 0, ki18n("ptedit"), version, ki18n("pairs theme editor"),
                     KAboutData::License_GPL, ki18n("(C) 2011 Marco Calignano"), KLocalizedString(), 0, "marco.calignano@gmail.com");
    KCmdLineArgs::init(argc, argv, &about);

    KApplication app;
    ptedit w;
    w.show();
    return app.exec();
}
