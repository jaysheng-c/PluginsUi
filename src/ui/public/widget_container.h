/**
  ********************************************************************************
  * @file           : widget_container.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/15
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef WIDGET_CONTAINER_H
#define WIDGET_CONTAINER_H

#include <QWidget>

class WidgetContainer : public QObject {
public:
    explicit WidgetContainer(QObject *parent = nullptr) : QObject(parent) {}
    virtual QWidget *widget() = 0;
    virtual QString fileName() = 0;

    virtual void undo() = 0;
    virtual void redo() = 0;

    virtual void open(const QString &file) = 0;
    virtual void saveAs(const QString &file) = 0;
    virtual void save() = 0;

};

#endif //WIDGET_CONTAINER_H
