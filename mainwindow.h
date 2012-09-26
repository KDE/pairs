#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtCore/QModelIndex>

class PairsTheme;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:

	void elementSelected(const QModelIndex & item);
	void backSelected();
	void fileSelected();
	void doOpen();

private:
    Ui::MainWindow *ui;
    PairsTheme *pt;
};

#endif // MAINWINDOW_H
