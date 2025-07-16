/**
  ********************************************************************************
  * @file           : table_container.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/15
  * @version        : 1.0
  ********************************************************************************
  */

#include "table_container.h"
#include "table_view.h"

TableContainer::TableContainer(QObject *parent)
    : WidgetContainer(parent), m_table(new TableView)
{
    m_table->initTable();
}

TableContainer::~TableContainer()
{
    if (!m_table.isNull() && !m_table->parent()) {
        m_table->deleteLater();
    }
}

QWidget *TableContainer::widget()
{
    return m_table;
}

QString TableContainer::fileName()
{
    return {};
}

void TableContainer::undo()
{
}

void TableContainer::redo()
{
}
