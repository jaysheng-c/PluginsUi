/**
  ********************************************************************************
  * @file           : init_left_tool_bar.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/30
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef INIT_LEFT_TOOL_BAR_H
#define INIT_LEFT_TOOL_BAR_H

#include "ui/internal/init_ui.h"

class InitLeftToolBar final : public InitUi {
public:
    explicit InitLeftToolBar(MainWindow *window);
    void init(QWidget *ui) override;
};



#endif //INIT_LEFT_TOOL_BAR_H
