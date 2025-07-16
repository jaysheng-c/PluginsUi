/**
  ********************************************************************************
  * @file           : table_view.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/14
  * @version        : 1.0
  ********************************************************************************
  */

#include "table_view.h"

#include <QKeyEvent>

#include "table_model.h"

TableView::TableView(QWidget *parent)
    : QTableView(parent), m_model(new TableModel(this))
{
    this->setFocusPolicy(Qt::ClickFocus);
}

void TableView::initTable()
{
    this->setModel(m_model);
}

void TableView::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "TableView";
    if (event->modifiers() & Qt::CTRL) {
        // 忽略掉该事件，由父窗口进行处理
        event->ignore();
        return;
    }
    QTableView::keyPressEvent(event);
}
