#ifndef MAINWINDOWVIEW_H
#define MAINWINDOWVIEW_H

#include <QtGui/QWidget>
#include <QtCore/QModelIndex>
#include <QtGui/QItemSelection>

class QXmlStreamWriter;
class PairsTheme;
class ThemeModel;
class QStandardItem;
class MainWindow;

namespace Ui {
class MainWindowView;
}

class MainWindowView : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWindowView(QWidget *parent = 0);
    ~MainWindowView();
    void widgetsHide();
    void clearUi(const QString &path);
    void writeXmlCommon(QXmlStreamWriter *stream);
    Ui::MainWindowView *ui(){return m_ui;};
    void setUi(PairsTheme *theme);
    void setModel(ThemeModel *model);
    bool check();
    QString checkString() const {return m_checkMessage;};

public slots:
    void elementSelected(const QModelIndex & item);
    void backSelected();
    void fileSelected();
    void selectionChanged(const QItemSelection& selected, const QItemSelection&);
    void wordChanged(const QString &word);
    void addElement();
    void deleteElement();
    void addFeature(int index);

private:
    MainWindow *m_parent;
    Ui::MainWindowView *m_ui;
    QString m_checkMessage;
    QString m_path;
    ThemeModel *m_model;
    PairsTheme *m_pt;
    QStandardItem *m_selectedItem;

};

#endif // MAINWINDOWVIEW_H
