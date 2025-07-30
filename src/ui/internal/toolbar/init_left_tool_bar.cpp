/**
  ********************************************************************************
  * @file           : init_left_tool_bar.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/30
  * @version        : 1.0
  ********************************************************************************
  */

#include "init_left_tool_bar.h"
#include "main_tool_bar.h"
#include "ui/internal/main_dock_widget.h"
#include "ui/internal/main_tree_view.h"
#include "ui/internal/main_window.h"

InitLeftToolBar::InitLeftToolBar(MainWindow *window)
    : InitUi(window)
{
}

void InitLeftToolBar::init(QWidget *ui)
{
    auto *toolBar = qobject_cast<MainToolBar*>(ui);
    if (toolBar == nullptr) {
        return;
    }
    if (m_window.isNull()) {
        return;
    }
    auto *docker = new MainDockWidget("FileDocker", m_window);
    docker->setObjectName("FileDocker");
    docker->setAllowedAreas(Qt::LeftDockWidgetArea);
    m_window->addDockWidget(Qt::LeftDockWidgetArea, docker);
    (void) QObject::connect(docker, &QDockWidget::visibilityChanged, [=](const bool visible) {
       if (auto *fileAction = toolBar->findChild<QAction*>("File")) {
           fileAction->setChecked(visible);
       }
    });

    auto *treeView = new MainTreeView(docker);
    docker->setWidget(treeView);
    treeView->initTree();
    for (int i {0}; i < 4; ++i) {
        if (const auto &[flag, msg] = treeView->addNode(QString::number(i), i); !flag) {
            continue;
        }
        for (int j {0}; j < 3; ++j) {
            (void) treeView->addNode(QString::number(j), i);
        }
    }

    auto *action = toolBar->addAction(QIcon(":/image/file.png"), "File", [=](const bool checked) {
        docker->setVisible(checked);
        if (auto *fileAction = toolBar->findChild<QAction*>("File")) {
            fileAction->setIcon(checked ? QIcon(":/image/file_selected.png") : QIcon(":/image/file.png"));
       }
    });
    action->setObjectName("File");
    action->setCheckable(true);

}
