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


#include <QToolBar>
#include <QTimer>

#include "main_dock_widget.h"
#include "main_tree_view.h"
#include "main_window.h"
#include "table/table_container.h"
#include "table/table_data.h"

#include "toolbar/init_left_tool_bar.h"

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
        m_mainWindow->addToolBar(Qt::RightToolBarArea, toolBar);

        auto *action = toolBar->addAction(QIcon(":/image/ai.png"), "Ai", [=](const bool checked) {
            auto *docker = m_mainWindow->findChild<QDockWidget*>("AiDocker");
            if (!docker) {
                docker = new MainDockWidget("AiDocker", m_mainWindow);
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

    InitLeftToolBar(m_mainWindow).init(m_mainWindow->findChild<QToolBar*>("left_tool_bar"));
}

UiLoader::~UiLoader()
{
    m_mainWindow->deleteLater();
}

void UiLoader::show()
{
    if (m_mainWindow) {
        m_mainWindow->resize(1400, 800);
        m_mainWindow->show();
    }
}

#include "moc_loader.cpp"