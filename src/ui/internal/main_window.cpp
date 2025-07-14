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

#include "table/table_view.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto *table = new TableView(this);
    table->initTable();
    this->setCentralWidget(table);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    for (auto *child : this->children()) {
        if (const auto *widget = qobject_cast<QWidget *>(child)) {
            qDebug() << widget << widget->hasFocus();
        }
    }
    if (event->modifiers() & Qt::CTRL) {
        qDebug() << __FUNCTION__ << "CTRL" << event->modifiers();
        event->accept();
        return;
    }
    QMainWindow::keyPressEvent(event);
}
