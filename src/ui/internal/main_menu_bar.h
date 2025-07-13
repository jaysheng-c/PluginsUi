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


class ExtMenu : public QMenu {
Q_OBJECT
signals:
    void extTriggered(const QString &component, int type);
public:
    explicit ExtMenu(QWidget *parent = nullptr) : QMenu(parent) {}
};

class MainMenuBar final : public QMenuBar {
Q_OBJECT
signals:
    void trigger(int type);
    void extTriggerd(const QString &component, int type);   // 组件名称, 类型
public:
    explicit MainMenuBar(QWidget *parent = nullptr);
    ~MainMenuBar() override;
    void addExternPlugins(ExtMenu *menu);
private:
    Ui::MainMenuBar *ui;
};


#endif //MAIN_MENU_BAR_H
