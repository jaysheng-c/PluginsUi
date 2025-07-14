/**
  ********************************************************************************
  * @file           : ui_loader.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/06
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef LOADER_H
#define LOADER_H

#include <QObject>
#include <QPointer>

#include "global.h"

class MainWindow;


class UI_EXPORT UiLoader final : public QObject {
Q_OBJECT
Q_DISABLE_COPY_MOVE(UiLoader)
public:
    static UiLoader *instance();
    ~UiLoader() override;

    void show();
private:
    explicit UiLoader(QObject *parent = nullptr);

    QPointer<MainWindow> m_mainWindow;
};



#endif //LOADER_H
