/**
  ********************************************************************************
  * @file           : main_menu_bar.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/13
  * @version        : 1.0
  ********************************************************************************
  */

// You may need to build the project (run Qt uic code generator) to get "ui_main_menu_bar.h" resolved

#include "main_menu_bar.h"
#include "ui_main_menu_bar.h"


MainMenuBar::MainMenuBar(QWidget *parent)
    : QMenuBar(parent), ui(new Ui::MainMenuBar)
{
    ui->setupUi(this);
}

MainMenuBar::~MainMenuBar() { delete ui; }

void MainMenuBar::addExternPlugins(ExtMenu *menu)
{
    if (menu == nullptr) {
        qWarning() << "You can not add nullptr menu in MainMenuBar";
        return;
    }
    auto *pluginsMenu = this->findChild<QMenu*>("action_plugins");
    if (pluginsMenu == nullptr) {
        qCritical() << "Can not find plugins menu in MainMenuBar, please check the software integrity";
        return;
    }
    pluginsMenu->addMenu(menu);
    (void) connect(menu, &ExtMenu::extTriggered, this, &MainMenuBar::extTriggerd);
}
