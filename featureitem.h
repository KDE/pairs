#ifndef FEATUREITEM_H
#define FEATUREITEM_H

#include <QtGui/QStandardItem>
#include <QtCore/QModelIndex>
#include "pairstheme.h"

class FeatureItem : public QStandardItem
{
    public:
        explicit FeatureItem(CardType type, QString lang, QString src);

};

#endif //FEATUREITEM_H
