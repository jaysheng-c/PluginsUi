/**
  ********************************************************************************
  * @file           : main_dock_widget.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/19
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef MAIN_DOCK_WIDGET_H
#define MAIN_DOCK_WIDGET_H

#include <QDockWidget>

class MainDockWidget : public QDockWidget {
Q_OBJECT
public:
    explicit MainDockWidget(const QString &title, QWidget *parent = nullptr,
                            Qt::WindowFlags flags = Qt::WindowFlags());
    explicit MainDockWidget(QWidget *parent = nullptr);
};



#endif //MAIN_DOCK_WIDGET_H
