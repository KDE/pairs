#ifndef MEMORYTHEME_H
#define MEMORYTHEME_H
#include <QString>

struct ThemeItem
{
    QString imagePath;
    QString soundPath;
};

class MemoryTheme
{
    public:
        MemoryTheme(const QString& path);
        
        QString name() const;
        QString description() const;
        
        QList<ThemeItem> items() const;
};

#endif // MEMORYTHEME_H
