#include "memorytheme.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <KLocalizedString>

MemoryTheme::MemoryTheme(const QString& path)
{
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly)) {
        m_error = i18n("Could not open the theme file");
        return;
    }
    if(path.contains('/'))
        m_baseDir = path.left(path.lastIndexOf('/'));
    else
        m_baseDir = ".";
    
    QXmlStreamReader reader(&f);
    
    while (m_error.isEmpty() && !reader.atEnd()) {
        QXmlStreamReader::TokenType type = reader.readNext();
        
        if(type==QXmlStreamReader::StartDocument || type==QXmlStreamReader::EndDocument) {}
        else if (type==QXmlStreamReader::Characters)
            m_data += reader.text().toString();
        else if(type==QXmlStreamReader::StartElement) {
            m_data.clear();
            
            QString name = reader.name().toString();
         
            if(name=="item") {
                ThemeItem item;
                item.imagePath = reader.attributes().value("image").toString();
                item.soundPath = reader.attributes().value("sound").toString();
                m_items += item;
            }
        } else if (type==QXmlStreamReader::EndElement) {
//             qDebug() << "ssssss" << m_data << type;
            QString name = reader.name().toString();
            
            if(name=="description") m_description = m_data;
            else if(name=="description") m_name = m_data;
            else if(name=="back") m_backPath = m_data;
            else if(name=="name") m_name = m_data;
            else if(name=="item") {}
            else
                m_error = i18n("Unknown item '%1' found", reader.name().toString());
        } else {
            m_error = i18n("%1:%2 Unknown token in theme file", reader.lineNumber(), reader.columnNumber());
        }
    }
    
    if (reader.hasError()) {}
}
