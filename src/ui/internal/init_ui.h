/**
  ********************************************************************************
  * @file           : init_ui.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/30
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef INIT_UI_H
#define INIT_UI_H
#include <QPointer>

class QWidget;
class MainWindow;

class InitUi {
public:
    explicit InitUi(MainWindow *window);
    virtual ~InitUi() = default;
    virtual void init(QWidget *ui) = 0;

protected:
    QPointer<MainWindow> m_window;
};

#endif //INIT_UI_H
