/*
 * kmemory.h
 *
 * Copyright (C) 2008 Albert Astals Cid <aacid@kde.org>
 */
#ifndef KMEMORY_H
#define KMEMORY_H


#include <kxmlguiwindow.h>

class kmemoryView;
class KToggleAction;

class kmemory : public KXmlGuiWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    kmemory();

    /**
     * Default Destructor
     */
    virtual ~kmemory();

private slots:
    void newGame();
    
private:
    void setupActions();

private:
    kmemoryView *m_view;

    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
};

#endif // _KMEMORY_H_
