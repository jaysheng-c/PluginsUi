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
    qDebug() << "";
    for (auto *container : m_mainContainer) {
        if (const auto *widget = container->widget()) {
            qDebug() << widget << widget->hasFocus();
        }
    }
    if (event->modifiers() & Qt::CTRL) {
        qDebug() << Q_FUNC_INFO << "CTRL" << event->modifiers();
        event->accept();
        return;
    }
    QMainWindow::keyPressEvent(event);
}
