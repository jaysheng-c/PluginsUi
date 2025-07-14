/**
  ********************************************************************************
  * @file           : discrete_matrix.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/14
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef DISCRETE_MATRIX_H
#define DISCRETE_MATRIX_H

#include <QReadWriteLock>

class TableData;

class DiscreteMatrix final {
public:
    DiscreteMatrix();
    DiscreteMatrix(int rows, int columns);
    DiscreteMatrix(const DiscreteMatrix &other);
    DiscreteMatrix(DiscreteMatrix &&other) noexcept;
    DiscreteMatrix &operator=(const DiscreteMatrix &other);
    DiscreteMatrix &operator=(DiscreteMatrix &&other) noexcept;
    ~DiscreteMatrix();

    // get
    int rows() const;
    int columns() const;
    qsizetype count() const;
    TableData at(int row, int column) const;

    // set
    bool setData(int row, int column, const TableData &data);
    bool setData(int row, int column, TableData &&data);

    bool insertColumns(const int column, const int count);
    bool insertRows(const int row, const int count);
    bool removeColumns(const int column, const int count);
    bool removeRows(const int row, const int count);
private:
    class MatrixPrivate;
    MatrixPrivate *m_d;

    mutable QReadWriteLock m_lock;
};



#endif //DISCRETE_MATRIX_H
