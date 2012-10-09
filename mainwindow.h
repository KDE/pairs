#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtCore/QModelIndex>

class QItemSelection;
class PairsTheme;
class QDir;
class QStandardItem;
class ThemeModel;
class KUrlRequester;
class QProcess;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void open(const QString& path);

    
public slots:
    void elementSelected(const QModelIndex & item);
    void backSelected();
    void fileSelected();
    void doNew();
    void doOpen();
    void doSave();
    void doSaveAs();
    void doUpload();
    void doTry();
    void selectionChanged(const QItemSelection& selected, const QItemSelection&);
    void wordChanged(const QString &word);
    void addElement();
    void deleteElement();
    void addFeature(int index);
    void pairsFinished();
private:
    Ui::MainWindow *ui;
    PairsTheme *pt;
    QStandardItem *m_selectedItem;
    ThemeModel *m_model;
    QString m_file;
    QString m_gameFile;
    QString m_pairsFile;
    QString m_checkMessage;
    QDir *m_tmpDir;
    QProcess *m_process;

    QString copyFile(KUrlRequester *k);
    bool check();
    void newTmpDir(const QString &path);
    void extract(QString path);
    void compress(QString path);
    void widgetsHide();
};

#endif // MAINWINDOW_H
