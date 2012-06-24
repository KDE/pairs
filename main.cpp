#include"ptedit_1.h"
#include"kcheckcombobox.h"
int main(int argc,char *argv[])
{
QApplication app(argc,argv);
QWidget *widget=new QWidget;
Ui::ptedit_1.ui;
ui.setupUi(widget);
widget->show();
return app.exec();
}
