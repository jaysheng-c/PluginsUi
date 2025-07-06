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

class MainWindow;

#ifdef UI_LIBRARY
#define UI_EXPORT Q_DECL_EXPORT
#else
#define UI_EXPORT Q_DECL_IMPORT
#endif

class UI_EXPORT UiLoader final : public QObject {
Q_OBJECT
public:
    explicit UiLoader(QObject *parent = nullptr);
    ~UiLoader() override;

    void show();
private:

    QPointer<MainWindow> m_mainWindow;
};



#endif //LOADER_H
