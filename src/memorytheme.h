#ifndef MEMORYTHEME_H
#define MEMORYTHEME_H
#include <QString>
#include <QList>

struct ThemeItem
{
    QString imagePath;
    QString soundPath;
};

class MemoryTheme
{
    public:
        MemoryTheme(const QString& path);
        
        QString name() const { return m_name; }
        QString description() const { return m_description; }
        QString backPath() const { return m_backPath; }
        
        QList<ThemeItem> items() const { return m_items; }
        
        bool isCorrect() const { return m_error.isEmpty(); }
        QString error() const { return m_error; }
        
    private:
        QString m_data;
        
        QString m_name;
        QString m_description;
        QString m_backPath;
        QList<ThemeItem> m_items;
        
        QString m_error;
        QString m_baseDir;
};

#endif // MEMORYTHEME_H
