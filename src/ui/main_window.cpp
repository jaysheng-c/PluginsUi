/**
  ********************************************************************************
  * @file           : main_window.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/06/28
  * @version        : 1.0
  ********************************************************************************
  */

// You may need to build the project (run Qt uic code generator) to get "ui_main_window.h" resolved

#include "main_window.h"
#include "ui_main_window.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}
