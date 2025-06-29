/**
  ********************************************************************************
  * @file           : main_window.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/06/28
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};


#endif //MAIN_WINDOW_H
