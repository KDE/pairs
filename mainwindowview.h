#ifndef MAINWINDOWVIEW_H
#define MAINWINDOWVIEW_H

#include <QtGui/QWidget>
#include <QtCore/QModelIndex>

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
    Ui::MainWindowView *ui(){return m_ui;};
private:
    Ui::MainWindowView *m_ui;
};

#endif // MAINWINDOWVIEW_H
