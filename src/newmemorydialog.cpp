#include "newmemorydialog.h"
#include <KLocalizedString>
#include <KStandardDirs>
#include <QBoxLayout>
#include <QListWidget>

#include "ui_newmemorydialog.h"

NewMemoryDialog::NewMemoryDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::NewMemoryDialog)
{
    m_ui->setupUi(this);
    
    const QStringList list = KGlobal::dirs()->findAllResources("appdata", QLatin1String( "themes/*.memory" ));
    m_ui->themesList->addItems(list);
}
