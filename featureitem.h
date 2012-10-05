#ifndef FEATUREITEM_H
#define FEATUREITEM_H

#include <QtGui/QStandardItem>
#include <QtCore/QModelIndex>
#include "pairstheme.h"

class QXmlStreamWriter;

class FeatureItem : public QStandardItem
{
    public:
        explicit FeatureItem(CardType type, QString lang, QString src);
        void writeElement(QXmlStreamWriter *stream);

};

#endif //FEATUREITEM_H
