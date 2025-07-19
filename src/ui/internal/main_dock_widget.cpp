/**
  ********************************************************************************
  * @file           : main_docker_widget.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/19
  * @version        : 1.0
  ********************************************************************************
  */

#include "main_dock_widget.h"

constexpr char gStyle[] =
    "MainDockWidget {\n"
    "   background-color: #252526;\n"
    "   border: 1px solid #ccc;\n"
    "}\n\n";

MainDockWidget::MainDockWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(title, parent, flags)
{
    this->setFloating(false);
    // this->setTitleBarWidget(new QWidget(this));
    this->setFeatures(NoDockWidgetFeatures);
    this->setStyleSheet(gStyle);
    this->setMinimumWidth(100);
}

MainDockWidget::MainDockWidget(QWidget *parent)
    : MainDockWidget("", parent)
{

}
