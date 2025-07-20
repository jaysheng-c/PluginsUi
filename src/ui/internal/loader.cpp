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

    if (auto *toolBar = m_mainWindow->findChild<QToolBar*>("left_tool_bar")) {
        m_mainWindow->addToolBar(Qt::LeftToolBarArea, toolBar);

        auto *action = toolBar->addAction(QIcon(":/image/file.png"), "File", [=](const bool checked) {
            auto *docker = m_mainWindow->findChild<QDockWidget*>("FileDocker");
            if (!docker) {
                docker = new MainDockWidget("FileDocker", m_mainWindow);
                docker->setObjectName("FileDocker");
                docker->setAllowedAreas(Qt::LeftDockWidgetArea);
                m_mainWindow->addDockWidget(Qt::LeftDockWidgetArea, docker);
                (void) connect(docker, &QDockWidget::visibilityChanged, [=](const bool visible) {
                    if (auto *fileAction = toolBar->findChild<QAction*>("File")) {
                        fileAction->setChecked(visible);
                    }
                });
                auto *treeView = new MainTreeView(docker);
                docker->setWidget(treeView);
                treeView->initTree();
                QTimer::singleShot(2 * 1000, [=]() {
                    for (int i {0}; i < 4; ++i) {
                        if (const auto &[flag, msg] = treeView->addNode(QString::number(i), i); !flag) {
                            continue;
                        }
                        for (int j {0}; j < 3; ++j) {
                            treeView->addNode(QString::number(j), i);
                        }
                    }
                });

            }
            docker->setVisible(checked);
            if (auto *fileAction = toolBar->findChild<QAction*>("File")) {
                fileAction->setIcon(checked ? QIcon(":/image/file_selected.png") : QIcon(":/image/file.png"));
            }
        });
        action->setObjectName("File");
        action->setCheckable(true);

        toolBar->addAction("ai");
    }
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