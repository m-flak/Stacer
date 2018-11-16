#include "advanced_info_page.h"
#include "ui_advanced_info_page.h"

AdvancedInfoPage::AdvancedInfoPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdvancedInfoPage)
{
    ui->setupUi(this);

    init();
}

AdvancedInfoPage::~AdvancedInfoPage()
{
    delete ui;

    if (mInstalledApps.count() > 0)
    {
        for (auto a = mInstalledApps.begin(); a != mInstalledApps.end(); ++a)
        {
            auto *b = *a;
            delete b;
        }
    }
}

void AdvancedInfoPage::init()
{
    connect(this, &AdvancedInfoPage::signal_clearInstalledApps, this, &AdvancedInfoPage::clearInstalledApps);

}

void AdvancedInfoPage::refreshInstalledApps()
{

}

void AdvancedInfoPage::clearInstalledApps()
{
    QList<AppEntry*> cleared;

    if (mInstalledApps.count() > 0)
    {
        for (auto a = mInstalledApps.begin(); a != mInstalledApps.end(); ++a)
        {
            auto *b = *a;
            delete b;
        }
    }

    mInstalledApps = cleared;
}
