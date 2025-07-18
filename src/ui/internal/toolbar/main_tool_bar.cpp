/**
  ********************************************************************************
  * @file           : main_tool_bar.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/18
  * @version        : 1.0
  ********************************************************************************
  */

#include "main_tool_bar.h"

constexpr char gStyle[] =
    "QToolBar {"
        "background-color: #252526;         /* 深灰背景 */\n"
        "color: #d4d4d4;                    /* 浅灰文字 */\n"
        "spacing: 8px;\n"
        "padding: 2px 2px;\n"
        "border-bottom: 1px solid #333333;  /* 底部边框线 */\n"
    "}\n\n"
    "QToolBar QToolButton {\n"
    "   width: 32px;\n"
    "   height: 32px;\n"
    "   background: transparent;\n"
    "   border-radius: 5px;\n"
    "}\n\n"
    "QToolBar QToolButton:hover {\n"
    "   background-color: #3e3e42;      /* 悬停背景色 */\n"
    "}\n\n"
    "QToolBar QToolButton:checked {\n"
    "    background-color: #1083ee;     /* 蓝色选中效果 */\n"
    "}\n\n"
    "QToolBar QToolButton:checked:hover {\n"
    "    background-color: #1083ee;     /* 保持蓝色选中状态 */\n"
    "}\n\n"
    "QToolBar::separator {\n"
    "    width: 5px;\n"
    "    background: transparent;\n"
    "}";

MainToolBar::MainToolBar(QWidget *parent)
    : QToolBar(parent)
{
    this->setStyleSheet(gStyle);
    this->setMovable(false);
    this->setFloatable(false);
}
