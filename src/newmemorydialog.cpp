#include "newmemorydialog.h"
#include <KLocalizedString>
#include <KStandardDirs>
#include <QBoxLayout>
#include <QListWidget>
#include <QDebug>

#include "ui_newmemorydialog.h"
#include "memorytheme.h"

NewMemoryDialog::NewMemoryDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::NewMemoryDialog)
{
    m_ui->setupUi(this);
    
    const QStringList themes = KGlobal::dirs()->findAllResources("appdata", QLatin1String( "themes/*.memory" ));
    foreach(const QString& themePath, themes) {
        MemoryTheme theme(themePath);
        
        if(!theme.isCorrect()) {
            qWarning() << "uncorrect theme:" << themePath << theme.error();
        } else {
            m_ui->themesList->addItem(theme.name());
            m_themes += theme;
        }
    }
    m_ui->themesList->setCurrentItem(m_ui->themesList->item(0));
}

MemoryTheme NewMemoryDialog::theme() const
{
    int row = m_ui->themesList->currentRow();
    return m_themes.at(row);
}

int NewMemoryDialog::columns() const { return m_ui->columns->value(); }
int NewMemoryDialog::rows() const { return m_ui->rows->value(); }
