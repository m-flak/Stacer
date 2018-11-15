#include "advanced_info_page.h"
#include "ui_advanced_info_page.h"

AdvancedInfoPage::AdvancedInfoPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdvancedInfoPage)
{
    ui->setupUi(this);
}

AdvancedInfoPage::~AdvancedInfoPage()
{
    delete ui;
}
