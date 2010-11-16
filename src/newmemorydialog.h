#ifndef NEWMEMORYDIALOG_H
#define NEWMEMORYDIALOG_H

#include <kdialog.h>

namespace Ui { class NewMemoryDialog; }

class NewMemoryDialog
    : public QDialog
{
    Q_OBJECT
    public:
        explicit NewMemoryDialog(QWidget* parent = 0);
        
        
    private:
        Ui::NewMemoryDialog* m_ui;
};

#endif // NEWMEMORYDIALOG_H
