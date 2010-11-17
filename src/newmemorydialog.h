#ifndef NEWMEMORYDIALOG_H
#define NEWMEMORYDIALOG_H

#include <kdialog.h>
#include "memorytheme.h"

namespace Ui { class NewMemoryDialog; }

class NewMemoryDialog
    : public QDialog
{
    Q_OBJECT
    public:
        explicit NewMemoryDialog(QWidget* parent = 0);
        MemoryTheme theme() const;
        int rows() const;
        int columns() const;
        
    private:
        Ui::NewMemoryDialog* m_ui;
        QList<MemoryTheme> m_themes;
};

#endif // NEWMEMORYDIALOG_H
