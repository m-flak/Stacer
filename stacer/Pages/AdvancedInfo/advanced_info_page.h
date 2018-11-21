#ifndef ADVANCED_INFO_PAGE_H
#define ADVANCED_INFO_PAGE_H

#include <QWidget>
#include <QStandardItemModel> 			
#include <QList>
#include "Types/appentry.h"

namespace Ui {
class AdvancedInfoPage;
}

class AdvancedInfoPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdvancedInfoPage(QWidget *parent = nullptr);
    ~AdvancedInfoPage();

signals:
    void signal_clearInstalledApps();

private slots:
    void init();
    void refreshInstalledApps();
    void clearInstalledApps();

private:
    Ui::AdvancedInfoPage *ui;

    QStandardItemModel   mItemModel;

    QList<AppEntry*>     mInstalledApps;
};

#endif // ADVANCED_INFO_PAGE_H
