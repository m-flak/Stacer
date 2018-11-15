#ifndef ADVANCED_INFO_PAGE_H
#define ADVANCED_INFO_PAGE_H

#include <QWidget>

namespace Ui {
class AdvancedInfoPage;
}

class AdvancedInfoPage : public QWidget
{
    Q_OBJECT

public:
    explicit AdvancedInfoPage(QWidget *parent = nullptr);
    ~AdvancedInfoPage();

private:
    Ui::AdvancedInfoPage *ui;
};

#endif // ADVANCED_INFO_PAGE_H
