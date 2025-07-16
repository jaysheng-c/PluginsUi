/**
  ********************************************************************************
  * @file           : main_window.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/06
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class WidgetContainer;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void setWidgetContainer(WidgetContainer *container);

protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    bool handleCtrl(WidgetContainer *container, QKeyEvent *event);
    bool handleCtrlShift(WidgetContainer *container, QKeyEvent *event);
    bool handleCtrlAlt(WidgetContainer *container, QKeyEvent *event);
    Ui::MainWindow *ui;

    QVector<WidgetContainer*> m_mainContainer;
};


#endif //MAIN_WINDOW_H
