/**
  ********************************************************************************
  * @file           : main_menu_bar.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/13
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef MAIN_MENU_BAR_H
#define MAIN_MENU_BAR_H

#include <QMenuBar>


QT_BEGIN_NAMESPACE
namespace Ui { class MainMenuBar; }
QT_END_NAMESPACE

class MainMenuBar : public QMenuBar {
Q_OBJECT

public:
    explicit MainMenuBar(QWidget *parent = nullptr);
    ~MainMenuBar() override;

private:
    Ui::MainMenuBar *ui;
};


#endif //MAIN_MENU_BAR_H
