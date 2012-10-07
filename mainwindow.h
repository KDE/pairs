#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtCore/QModelIndex>

class QItemSelection;
class PairsTheme;
class QDir;
class QStandardItem;
class ThemeModel;
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
    void addElement();
    void deleteElement();
    void addFeature(int index);
private:
    Ui::MainWindow *ui;
    PairsTheme *pt;
    QStandardItem *m_selectedItem;
    ThemeModel *m_model;
    QString m_file;
    QString m_gameFile;
    QString m_checkMessage;
    QDir *m_tmpDir;

    bool check();
    void newTmpDir(const QString &path);
    void extract(QString path);
    void compress(QString path);
};

#endif // MAINWINDOW_H
