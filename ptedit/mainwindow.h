#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>
#include <QtCore/QModelIndex>

class QItemSelection;
class PairsTheme;
class QDir;
class QStandardItem;
class ThemeModel;
class KUrlRequester;
class QProcess;
class MainWindowView;

class MainWindow : public KXmlGuiWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void open(const QString& path);
    
public slots:
    void doNew();
    void doOpen();
    void doSave();
    void doSaveAs();
//    void doUpload();
    void doTry();
    void pairsFinished();
    QString copyFile(KUrlRequester *k);

private:
    MainWindowView *m_mainWidget;
    PairsTheme *m_pt;
    QStandardItem *m_selectedItem;
    ThemeModel *m_model;
    QString m_file;
    QString m_gameFile;
    QString m_pairsFile;
    QDir *m_tmpDir;
    QProcess *m_process;

    void newTmpDir(const QString &path);
    void extract(QString path);
    void compress(QString path);
};

#endif // MAINWINDOW_H
