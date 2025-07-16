/**
  ********************************************************************************
  * @file           : main_window.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/06
  * @version        : 1.0
  ********************************************************************************
  */

// You may need to build the project (run Qt uic code generator) to get "ui_main_window.h" resolved

#include "main_window.h"
#include "ui_main_window.h"

#include <QFileDialog>
#include <QKeyEvent>

#include "widget_container.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWidgetContainer(WidgetContainer *container)
{
    if (m_mainContainer.contains(container)) {
        return;
    }
    m_mainContainer.append(container);
    this->setCentralWidget(container->widget());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    bool flag = false;
    for (auto *container: m_mainContainer) {
        const auto *widget = container->widget();
        Q_ASSERT_X(widget, "MainWindow::keyPressEvent", "widget is null");
        if (!widget->hasFocus()) {
            continue;
        }
        if (event->modifiers().testFlags(Qt::ControlModifier | Qt::ShiftModifier)) {
            flag |= handleCtrlShift(container, event);
        } else if (event->modifiers().testFlags(Qt::ControlModifier | Qt::AltModifier)) {
            flag |= handleCtrlAlt(container, event);
        } else if (event->modifiers().testFlag(Qt::ControlModifier)) {
            flag |= handleCtrl(container, event);
        }
    }
    if (!flag) {
        QMainWindow::keyPressEvent(event);
    }
}

bool MainWindow::handleCtrl(WidgetContainer *container, QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Z:
            container->redo();
            break;
        case Qt::Key_Y:
            container->undo();
            break;
        case Qt::Key_S:
            if (container->fileName().isEmpty()) {
                container->save();
                break;
            }
            return handleCtrlAlt(container, event);
        default: return false;
    }
    event->accept();
    return true;
}

bool MainWindow::handleCtrlShift(WidgetContainer *container, QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Z:
            container->undo();
            break;
        default: return false;
    }
    event->accept();
    return true;
}

bool MainWindow::handleCtrlAlt(WidgetContainer *container, QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_S:
            container->saveAs(QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                           tr("Text Files (*.txt);;All Files (*)")));
            break;
        default: return false;
    }
    event->accept();
    return true;
}
