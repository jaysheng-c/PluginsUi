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

#include <QDockWidget>
#include <QToolBar>
#include <QToolButton>

#include "main_window.h"
#include "table/table_container.h"
#include "table/table_data.h"

UiLoader *UiLoader::instance()
{
    static UiLoader inst;
    return &inst;
}

UiLoader::UiLoader(QObject *parent)
    : QObject(parent), m_mainWindow(new MainWindow)
{
    TableData::initFontMap();
    m_mainWindow->setWidgetContainer(new TableContainer(this));

    if (auto *toolBar = m_mainWindow->findChild<QToolBar*>("right_tool_bar")) {
        toolBar->setStyleSheet(
        "QToolBar {"
                "background-color: #252526;         /* 深灰背景 */\n"
                "color: #d4d4d4;                    /* 浅灰文字 */\n"
                "spacing: 8px;\n"
                "padding: 2px 2px;\n"
                "border-bottom: 1px solid #333333;  /* 底部边框线 */\n"
            "}\n\n"
            "QToolBar QToolButton {\n"
            "   width: 32px;\n"
            "   height: 32px;\n"
            "   background: transparent;\n"
            "   border-radius: 5px;\n"
            "}\n\n"
            "QToolBar QToolButton:hover {\n"
            "   background-color: #3e3e42;      /* 悬停背景色 */\n"
            "}\n\n"
            "QToolBar QToolButton:checked {\n"
            "    background-color: #1083ee;     /* 蓝色选中效果 */\n"
            "}\n\n"
            "QToolBar QToolButton:checked:hover {\n"
            "    background-color: #1083ee;     /* 保持蓝色选中状态 */\n"
            "}\n\n"
            "QToolBar::separator {\n"
            "    width: 5px;\n"
            "    background: transparent;\n"
            "}"
            );

        // toolBar->setIconSize(QSize(32, 32));
        toolBar->setFixedWidth(36);
        toolBar->setMovable(false);
        toolBar->setFloatable(false);
        m_mainWindow->addToolBar(Qt::RightToolBarArea, toolBar);

        auto *action = toolBar->addAction(QIcon(":/image/ai.png"), "Ai", [=](const bool checked) {
            auto *docker = m_mainWindow->findChild<QDockWidget*>("AiDocker");
            if (!docker) {
                docker = new QDockWidget("AiDocker", m_mainWindow);
                docker->setObjectName("AiDocker");
                docker->setAllowedAreas(Qt::RightDockWidgetArea);
                m_mainWindow->addDockWidget(Qt::RightDockWidgetArea, docker);
                (void) connect(docker, &QDockWidget::visibilityChanged, [=](const bool visible) {
                    if (auto *aiAction = toolBar->findChild<QAction*>("Ai")) {
                        aiAction->setChecked(visible);
                    }
                });
            }
            docker->setVisible(checked);
            if (auto *aiAction = toolBar->findChild<QAction*>("Ai")) {
                aiAction->setIcon(checked ? QIcon(":/image/ai_selected.png") : QIcon(":/image/ai.png"));
            }
        });
        action->setObjectName("Ai");
        action->setCheckable(true);
    }
}

UiLoader::~UiLoader()
{
    m_mainWindow->deleteLater();
}

void UiLoader::show()
{
    if (m_mainWindow) {
        m_mainWindow->resize(800, 600);
        m_mainWindow->show();
    }
}

#include "moc_loader.cpp"