/********************************************************************************
** Form generated from reading UI file 'ptedit_1.ui'
**
** Created: Thu Jun 21 19:36:04 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef PTEDIT_1_H
#define PTEDIT_1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollBar>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "kcombobox.h"
#include "kicondialog.h"
#include "klineedit.h"
#include "kpushbutton.h"
#include "kseparator.h"
#include "kurlrequester.h"
#include "kcheckcombobox.h"
#include "ptedit_1.h"
#include "kdepim_export.h"

QT_BEGIN_NAMESPACE
int main()
{

class Ui_MainWindow
{
public:
    QAction *action_New;
    QAction *action_Save;
    QAction *action_Exit;
    QAction *action_exit;
    QAction *action_cut;
    QAction *action_copy;
    QAction *action_paste;
    QAction *action_about;
    QAction *action_about_Qt;
    QAction *action_open_file;
    QAction *action_upload;
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QWidget *widget_2;
    QLabel *label;
    QLabel *label_2;
    KSeparator *kseparator;
    QSplitter *splitter;
    KPIM::KCheckComboBox *kpim__kcheckcombobox;
    QDialogButtonBox *buttonBox;
    QSplitter *splitter_2;
    KUrlRequester *exporterUrl;
    KPushButton *exporterButton;
    QCommandLinkButton *commandLinkButton;
    QGroupBox *groupBox;
    KSeparator *kseparator_2;
    KSeparator *kseparator_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    KIconButton *kiconbutton;
    QGroupBox *groupBox_2;
    KSeparator *kseparator_4;
    QScrollBar *verticalScrollBar_3;
    KLineEdit *klineedit;
    QScrollBar *horizontalScrollBar;
    QScrollBar *verticalScrollBar;
    QLabel *label_3;
    QScrollBar *horizontalScrollBar_2;
    QScrollBar *verticalScrollBar_2;
    QScrollBar *horizontalScrollBar_3;
    QSplitter *splitter_3;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QMenu *menu_help;
    QMenu *menu_upload;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(792, 600);
        MainWindow->setProperty("widget", QVariant(true));
        action_New = new QAction(MainWindow);
        action_New->setObjectName(QString::fromUtf8("action_New"));
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QString::fromUtf8("action_exit"));
        action_cut = new QAction(MainWindow);
        action_cut->setObjectName(QString::fromUtf8("action_cut"));
        action_copy = new QAction(MainWindow);
        action_copy->setObjectName(QString::fromUtf8("action_copy"));
        action_paste = new QAction(MainWindow);
        action_paste->setObjectName(QString::fromUtf8("action_paste"));
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QString::fromUtf8("action_about"));
        action_about_Qt = new QAction(MainWindow);
        action_about_Qt->setObjectName(QString::fromUtf8("action_about_Qt"));
        action_open_file = new QAction(MainWindow);
        action_open_file->setObjectName(QString::fromUtf8("action_open_file"));
        action_upload = new QAction(MainWindow);
        action_upload->setObjectName(QString::fromUtf8("action_upload"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(200, 10, 251, 531));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(horizontalLayoutWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 241, 231));
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 0, 181, 21));
        label->setMinimumSize(QSize(0, 15));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 100, 211, 31));
        kseparator = new KSeparator(widget_2);
        kseparator->setObjectName(QString::fromUtf8("kseparator"));
        kseparator->setGeometry(QRect(0, 90, 251, 16));
        splitter = new QSplitter(widget_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setGeometry(QRect(30, 20, 156, 48));
        splitter->setOrientation(Qt::Vertical);
        kpim__kcheckcombobox = new KPIM::KCheckComboBox(splitter);
        kpim__kcheckcombobox->setObjectName(QString::fromUtf8("kpim__kcheckcombobox"));
        splitter->addWidget(kpim__kcheckcombobox);
        buttonBox = new QDialogButtonBox(splitter);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        splitter->addWidget(buttonBox);
        splitter_2 = new QSplitter(widget_2);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setGeometry(QRect(40, 130, 149, 47));
        splitter_2->setOrientation(Qt::Vertical);
        exporterUrl = new KUrlRequester(splitter_2);
        exporterUrl->setObjectName(QString::fromUtf8("exporterUrl"));
        splitter_2->addWidget(exporterUrl);
        exporterButton = new KPushButton(splitter_2);
        exporterButton->setObjectName(QString::fromUtf8("exporterButton"));
        splitter_2->addWidget(exporterButton);
        commandLinkButton = new QCommandLinkButton(widget);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(40, 480, 168, 41));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 260, 231, 171));
        kseparator_2 = new KSeparator(widget);
        kseparator_2->setObjectName(QString::fromUtf8("kseparator_2"));
        kseparator_2->setGeometry(QRect(0, 220, 251, 16));
        kseparator_3 = new KSeparator(widget);
        kseparator_3->setObjectName(QString::fromUtf8("kseparator_3"));
        kseparator_3->setGeometry(QRect(10, 460, 241, 20));

        horizontalLayout->addWidget(widget);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(460, 10, 311, 531));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        kiconbutton = new KIconButton(verticalLayoutWidget);
        kiconbutton->setObjectName(QString::fromUtf8("kiconbutton"));

        verticalLayout->addWidget(kiconbutton);

        groupBox_2 = new QGroupBox(verticalLayoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        kseparator_4 = new KSeparator(groupBox_2);
        kseparator_4->setObjectName(QString::fromUtf8("kseparator_4"));
        kseparator_4->setGeometry(QRect(0, 20, 301, 16));
        verticalScrollBar_3 = new QScrollBar(groupBox_2);
        verticalScrollBar_3->setObjectName(QString::fromUtf8("verticalScrollBar_3"));
        verticalScrollBar_3->setGeometry(QRect(300, 0, 16, 461));
        verticalScrollBar_3->setOrientation(Qt::Vertical);

        verticalLayout->addWidget(groupBox_2);

        klineedit = new KLineEdit(verticalLayoutWidget);
        klineedit->setObjectName(QString::fromUtf8("klineedit"));

        verticalLayout->addWidget(klineedit);

        horizontalScrollBar = new QScrollBar(centralwidget);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(0, 540, 811, 20));
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        verticalScrollBar = new QScrollBar(centralwidget);
        verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(780, 0, 16, 561));
        verticalScrollBar->setOrientation(Qt::Vertical);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 10, 151, 491));
        horizontalScrollBar_2 = new QScrollBar(centralwidget);
        horizontalScrollBar_2->setObjectName(QString::fromUtf8("horizontalScrollBar_2"));
        horizontalScrollBar_2->setGeometry(QRect(-10, 520, 201, 20));
        horizontalScrollBar_2->setOrientation(Qt::Horizontal);
        verticalScrollBar_2 = new QScrollBar(centralwidget);
        verticalScrollBar_2->setObjectName(QString::fromUtf8("verticalScrollBar_2"));
        verticalScrollBar_2->setGeometry(QRect(170, 10, 16, 511));
        verticalScrollBar_2->setOrientation(Qt::Vertical);
        horizontalScrollBar_3 = new QScrollBar(centralwidget);
        horizontalScrollBar_3->setObjectName(QString::fromUtf8("horizontalScrollBar_3"));
        horizontalScrollBar_3->setGeometry(QRect(450, 500, 331, 16));
        horizontalScrollBar_3->setOrientation(Qt::Horizontal);
        splitter_3 = new QSplitter(centralwidget);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setGeometry(QRect(0, 0, 0, 0));
        splitter_3->setOrientation(Qt::Vertical);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 792, 21));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Edit = new QMenu(menubar);
        menu_Edit->setObjectName(QString::fromUtf8("menu_Edit"));
        menu_help = new QMenu(menubar);
        menu_help->setObjectName(QString::fromUtf8("menu_help"));
        menu_upload = new QMenu(menubar);
        menu_upload->setObjectName(QString::fromUtf8("menu_upload"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Edit->menuAction());
        menubar->addAction(menu_help->menuAction());
        menubar->addAction(menu_upload->menuAction());
        menu_File->addSeparator();
        menu_File->addSeparator();
        menu_File->addSeparator();
        menu_File->addAction(action_open_file);
        menu_Edit->addAction(action_paste);
        menu_help->addAction(action_about);
        menu_upload->addAction(action_upload);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_New->setText(QApplication::translate("MainWindow", "&New", 0, QApplication::UnicodeUTF8));
        action_Save->setText(QApplication::translate("MainWindow", "&Save", 0, QApplication::UnicodeUTF8));
        action_Exit->setText(QApplication::translate("MainWindow", "&save as", 0, QApplication::UnicodeUTF8));
        action_exit->setText(QApplication::translate("MainWindow", "&exit", 0, QApplication::UnicodeUTF8));
        action_cut->setText(QApplication::translate("MainWindow", "&cut", 0, QApplication::UnicodeUTF8));
        action_copy->setText(QApplication::translate("MainWindow", "&copy", 0, QApplication::UnicodeUTF8));
        action_paste->setText(QApplication::translate("MainWindow", "&save", 0, QApplication::UnicodeUTF8));
        action_about->setText(QApplication::translate("MainWindow", "&try", 0, QApplication::UnicodeUTF8));
        action_about_Qt->setText(QApplication::translate("MainWindow", "&about Qt", 0, QApplication::UnicodeUTF8));
        action_open_file->setText(QApplication::translate("MainWindow", "&open file", 0, QApplication::UnicodeUTF8));
        action_upload->setText(QApplication::translate("MainWindow", "&upload", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Select a widget :", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Export file :Choose a target file  .", 0, QApplication::UnicodeUTF8));
        kpim__kcheckcombobox->clear();
        kpim__kcheckcombobox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Dock widget", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "tab widget", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "list widget", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "tree widget", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "table widget", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "group box", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "scroll area", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "tab widget", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "stacked widget", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "widget", 0, QApplication::UnicodeUTF8)
        );
        exporterButton->setText(QApplication::translate("MainWindow", "Export current project", 0, QApplication::UnicodeUTF8));
        commandLinkButton->setText(QApplication::translate("MainWindow", "Go back", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Working on .......", 0, QApplication::UnicodeUTF8));
        kiconbutton->setText(QApplication::translate("MainWindow", "Go !", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Help content ", 0, QApplication::UnicodeUTF8));
        klineedit->setText(QApplication::translate("MainWindow", "Help area..../...", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "              XML tree", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&open", 0, QApplication::UnicodeUTF8));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&save", 0, QApplication::UnicodeUTF8));
        menu_help->setTitle(QApplication::translate("MainWindow", "&try", 0, QApplication::UnicodeUTF8));
        menu_upload->setTitle(QApplication::translate("MainWindow", "&upload", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

QT_END_NAMESPACE

#endif // PTEDIT_1_H
return 0;
}
