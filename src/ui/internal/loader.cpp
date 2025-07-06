/**
  ********************************************************************************
  * @file           : ui_loader.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/06
  * @version        : 1.0
  ********************************************************************************
  */

#include "loader.h"

#include "main_window.h"

UiLoader::UiLoader(QObject *parent)
    : QObject(parent), m_mainWindow(new MainWindow)
{
}

UiLoader::~UiLoader()
{
    m_mainWindow->deleteLater();
}

void UiLoader::show()
{
    if (m_mainWindow)
        m_mainWindow->show(); {
    }
}

#include "moc_loader.cpp"