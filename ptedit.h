#ifndef PTEDIT_H
#define PTEDIT_H

#include <QtGui/QWidget>
#include "ui_ptedit.h"

class ptedit : public QWidget
{
    Q_OBJECT

public:
    ptedit(QWidget *parent = 0);
    ~ptedit();

private:
    Ui::pteditClass ui;
};

#endif // PTEDIT_H
