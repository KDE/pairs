/*
 * kmemory.h
 *
 * Copyright (C) 2008 Albert Astals Cid <aacid@kde.org>
 */
#ifndef KMEMORY_H
#define KMEMORY_H


#include <kxmlguiwindow.h>

#include "ui_prefs_base.h"

class kmemoryView;
class QPrinter;
class KToggleAction;
class KUrl;

/**
 * This class serves as the main window for kmemory.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author Albert Astals Cid <aacid@kde.org>
 * @version 0.1
 */
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
    void fileNew();
    void optionsPreferences();

private:
    void setupActions();

private:
    Ui::prefs_base ui_prefs_base ;
    kmemoryView *m_view;

    QPrinter   *m_printer;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
};

#endif // _KMEMORY_H_
