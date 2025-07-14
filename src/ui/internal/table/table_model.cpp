/**
  ********************************************************************************
  * @file           : table_model.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/14
  * @version        : 1.0
  ********************************************************************************
  */

#include "table_model.h"
#include "table_data.h"

constexpr int COLUMN_COUNT = 20;
constexpr int ROW_COUNT = 100;

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent), m_data(std::make_unique<DiscreteMatrix>())
{
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data->rows();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data->columns();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }
    const auto data = m_data->at(index.row(), index.column());
    switch (role) {
        case Qt::DisplayRole:       return data.data(TableData::Display);
        case Qt::EditRole:          return data.data(TableData::Real);
        case Qt::TextAlignmentRole: return data.data(TableData::Align);
        case Qt::ForegroundRole:    return data.data(TableData::Foreground);
        case Qt::BackgroundRole:    return data.data(TableData::Background);
        case Qt::FontRole:          return data.data(TableData::Font);
        default: break;
    }
    return {};
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (index.isValid()) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    }
    return Qt::NoItemFlags;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QAbstractTableModel::headerData(section, orientation, role);
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return {};
    }
    auto data = m_data->at(index.row(), index.column());
    bool flag = false;
    switch (role) {
        case Qt::DisplayRole:       flag = data.setData(TableData::Display, value); break;
        case Qt::EditRole:          flag = data.setData(TableData::Real, value); break;
        case Qt::TextAlignmentRole: flag = data.setData(TableData::Align, value); break;
        case Qt::ForegroundRole:    flag = data.setData(TableData::Foreground, value); break;
        case Qt::BackgroundRole:    flag = data.setData(TableData::Background, value); break;
        case Qt::FontRole:          flag = data.setData(TableData::Font, value); break;
        default:                    return QAbstractTableModel::setData(index, value, role);
    }
    if (flag) {
        flag &= m_data->setData(index.row(), index.column(), data);
        emit dataChanged(index, index, {role});
    }
    return flag;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    return QAbstractTableModel::insertRows(row, count, parent);
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    return QAbstractTableModel::removeRows(row, count, parent);
}

bool TableModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    return QAbstractTableModel::insertColumns(column, count, parent);
}

bool TableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    return QAbstractTableModel::removeColumns(column, count, parent);
}
