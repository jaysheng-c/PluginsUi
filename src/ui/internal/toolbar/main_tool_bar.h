/**
  ********************************************************************************
  * @file           : main_tool_bar.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/18
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef MAIN_TOOL_BAR_H
#define MAIN_TOOL_BAR_H

#include <QToolBar>

class MainToolBar : public QToolBar {
Q_OBJECT
public:
    explicit MainToolBar(QWidget *parent = nullptr);
};



#endif //MAIN_TOOL_BAR_H
