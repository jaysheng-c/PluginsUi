/**
  ********************************************************************************
  * @file           : table_container.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/15
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef TABLE_CONTAINER_H
#define TABLE_CONTAINER_H

#include <QPointer>
#include "widget_container.h"

class TableView;

class TableContainer final : public WidgetContainer {
Q_OBJECT
public:
    explicit TableContainer(QObject *parent = nullptr);
    ~TableContainer() override;

    QWidget *widget() override;
    void undo() override;
    void redo() override;

private:
    QPointer<TableView> m_table;
};



#endif //TABLE_CONTAINER_H
