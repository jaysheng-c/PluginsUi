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

constexpr char styleString[] =
    "/* 菜单栏整体样式 */\n"
    "QMenuBar {\n"
    "   background-color: #252526;  /* 深灰背景 */\n"
    "   color: #d4d4d4;             /* 浅灰文字 */\n"
    "   spacing: 8px;\n"
    "   padding: 5px 5px;\n"
    "   border-bottom: 1px solid #333333;  /* 底部边框线 */\n"
    "}\n\n"
    "/* 菜单项悬停/选中状态 */\n"
    "QMenuBar::item {\n"
    "    padding: 3px 5px;		/* 增加内边距 */\n"
    "    margin: 0 2px;		 	/* 项之间的间距 */\n"
    "    border-radius: 3px;\n"
    "    background-color: transparent;\n"
    "}\n\n"
    "/* 鼠标悬停效果 */\n"
    "QMenuBar::item:hover {\n"
    "    background-color: #3e3e42; /* 悬停背景色 */\n"
    "    color: #ffffff;            /* 悬停文字颜色 */\n"
    "}\n\n"
    "/* 选中/激活状态 */\n"
    "QMenuBar::item:selected,\n"
    "QMenuBar::item:pressed {\n"
    "    background-color: rgba(122, 122, 122, 180);\n"
    "    color: #ffffff;\n"
    "}\n\n"
    "/* 禁用状态 */\n"
    "QMenuBar::item:disabled {\n"
    "    color: #656565;\n"
    "}\n\n"
    "/* 下拉箭头样式 */\n"
    "QMenuBar::item:menu-indicator {\n"
    "    image: none;  /* 隐藏默认箭头 */\n"
    "}\n\n"
    "/* 下拉菜单样式 */\n"
    "QMenu {\n"
    "    background-color: #2d2d2d;\n"
    "    border: 1px solid #454545;\n"
    "    color: #d4d4d4;\n"
    "    padding: 5px;\n"
    "}\n\n"
    "QMenu::item {\n"
    "    height: 20px;                 /* 固定高度（可选） */\n"
    "    min-height: 20px;             /* 最小高度（推荐） */\n"
    "    min-width: 100px;\n"
    "    padding: 5px 10px 5px 30px;    /* 上下 5px，左右 20px */\n"
    "    margin: 2px 0;                 /* 上下间距 2px，左右 0 */\n"
    "    background-color: transparent; /* 默认透明 */\n"
    "    border-radius: 5px\n"
    "}\n\n"
    "QMenu::item:selected {\n"
    "    background-color: #2e436e;\n"
    "    color: white;\n"
    "}\n\n"
    "QMenu::separator {\n"
    "    height: 1px;\n"
    "    background: #454545;\n"
    "    margin: 4px 0;\n"
    "}";


MainMenuBar::MainMenuBar(QWidget *parent)
    : QMenuBar(parent), ui(new Ui::MainMenuBar)
{
    ui->setupUi(this);
    this->setStyleSheet(QString::fromStdString(styleString));
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
    (void) connect(menu, &ExtMenu::extTriggered, this, &MainMenuBar::extTriggered);
}
