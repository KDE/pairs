#ifndef THEMEMODEL_H
#define THEMEMODEL_H

#include <QtGui/QStandardItemModel>
#include "pairstheme.h"
class ThemeModel : public QStandardItemModel
{
    Q_OBJECT
    public:
    enum ThemeModelRoles {
         CardTypeRole = Qt::UserRole + 1,
         LanguageRole,
         PathRole
     };
        explicit ThemeModel(PairsTheme &t, QObject* parent = 0);
        explicit ThemeModel(QObject* parent = 0);
        void removeItem(QStandardItem *selectedItem);
        void insertItem(QStandardItem *newItem);
        void insertFeature(QStandardItem *newItem, QStandardItem *parent);
};

#endif // THEMEMODEL_H
