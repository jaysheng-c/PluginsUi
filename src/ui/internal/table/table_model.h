/**
  ********************************************************************************
  * @file           : table_model.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/14
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include <memory>
#include <QAbstractTableModel>

#include "discrete_matrix.h"

class TableModel final : public QAbstractTableModel {
Q_OBJECT
public:
    explicit TableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // set & delete
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool insertRows(int position, int rows, const QModelIndex &parent) override;
    bool removeRows(int position, int rows, const QModelIndex &parent) override;
    bool insertColumns(int position, int columns, const QModelIndex &parent) override;
    bool removeColumns(int position, int columns, const QModelIndex &parent) override;

private:
    std::unique_ptr<DiscreteMatrix> m_data;

};


#endif //TABLE_MODEL_H
