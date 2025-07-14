/**
  ********************************************************************************
  * @file           : discrete_matrix.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/14
  * @version        : 1.0
  ********************************************************************************
  */

#include "discrete_matrix.h"

#include <QDebug>
#include <QHash>
#include <QQueue>
#include <QReadWriteLock>
#include <QThreadPool>

#include "table_data.h"

namespace {

constexpr int COLUMN_COUNT{20};
constexpr int ROW_COUNT{100};
constexpr int SHARD_COUNT{16};
constexpr int COL_CACHE_INDEX{0};
constexpr int ROW_CACHE_INDEX{1};

struct Shard {
    QHash<qsizetype, TableData> data;
    mutable QReadWriteLock lock;
};

qsizetype shard(const qsizetype index)
{
    return static_cast<qsizetype>(qHash(index) % SHARD_COUNT);
}

class IndexInit {
public:
    QVector<qsizetype> operator()(const qsizetype count) const
    {
        QVector<qsizetype> res(count);
        for (int i{0}; i < count; ++i) {
            res[i] = i;
        }
        return res;
    }
};

}

class DiscreteMatrix::MatrixPrivate {
public:
    MatrixPrivate(const int rows, const int columns)
        : rows(rows), columns(columns), rowIndexes(IndexInit()(rows)), columnIndexes(IndexInit()(columns))
    {
    }
    MatrixPrivate(const MatrixPrivate &other)
    {
        rows = other.rows;
        columns = other.columns;
        rowIndexes = other.rowIndexes;
        columnIndexes = other.columnIndexes;
        for (int i{0}; i < SHARD_COUNT; ++i) {
            QWriteLocker tLocker(&(data[i].lock));
            QReadLocker sLocker(&(other.data[i].lock));
            data[i].data = other.data[i].data;
        }
    }
    MatrixPrivate(MatrixPrivate &&other) noexcept
    {
        rows = other.rows;
        columns = other.columns;
        rowIndexes = std::move(other.rowIndexes);
        columnIndexes = std::move(other.columnIndexes);
        for (int i{0}; i < SHARD_COUNT; ++i) {
            QWriteLocker tLocker(&(data[i].lock));
            QWriteLocker sLocker(&(other.data[i].lock));
            data[i].data = std::move(other.data[i].data);
        }
    }
    MatrixPrivate &operator=(const MatrixPrivate &other)
    {
        if (this == &other) {
            return *this;
        }
        rows = other.rows;
        columns = other.columns;
        rowIndexes = other.rowIndexes;
        columnIndexes = other.columnIndexes;
        for (int i{0}; i < SHARD_COUNT; ++i) {
            QWriteLocker tLocker(&(data[i].lock));
            QReadLocker sLocker(&(other.data[i].lock));
            data[i].data = other.data[i].data;
        }
        return *this;
    }
    MatrixPrivate &operator=(MatrixPrivate &&other) noexcept
    {
        if (this == &other) {
            return *this;
        }
        rows = other.rows;
        columns = other.columns;
        rowIndexes = std::move(other.rowIndexes);
        columnIndexes = std::move(other.columnIndexes);
        for (int i{0}; i < SHARD_COUNT; ++i) {
            QWriteLocker tLocker(&(data[i].lock));
            QWriteLocker sLocker(&(other.data[i].lock));
            data[i].data = std::move(other.data[i].data);
        }
        return *this;
    }

    qsizetype index(const qsizetype row, const qsizetype column) const
    {
        if (column >= columnIndexes.size()) {
            qWarning() << "column out of range";
            return -1;
        }
        if (row >= rowIndexes.size()) {
            qWarning() << "row out of range";
            return -1;
        }
        return rowIndexes.at(row) << 32 | columnIndexes.at(column);
    }


    int rows;
    int columns;
    QVector<qsizetype> rowIndexes;
    QVector<qsizetype> columnIndexes;
    std::array<QQueue<qsizetype>, 2> invalidCache;
    std::array<Shard, SHARD_COUNT> data;
};

DiscreteMatrix::DiscreteMatrix() : DiscreteMatrix(ROW_COUNT, COLUMN_COUNT)
{
}

DiscreteMatrix::DiscreteMatrix(int rows, int columns)
    : m_d(new MatrixPrivate(rows, columns))
{
}

DiscreteMatrix::DiscreteMatrix(const DiscreteMatrix &other)
{
    m_d = new MatrixPrivate(*other.m_d);
}

DiscreteMatrix::DiscreteMatrix(DiscreteMatrix &&other) noexcept
{
    m_d = other.m_d;
    other.m_d = nullptr;
}

DiscreteMatrix & DiscreteMatrix::operator=(const DiscreteMatrix &other)
{
    if (this == &other) {
        return *this;
    }
    if (m_d) {
        *m_d = *other.m_d;
    } else {
        m_d = new MatrixPrivate(*other.m_d);
    }
    return *this;
}

DiscreteMatrix & DiscreteMatrix::operator=(DiscreteMatrix &&other) noexcept
{
    if (this == &other) {
        return *this;
    }
    if (m_d) {
        delete m_d;
    }
    m_d = other.m_d;
    other.m_d = nullptr;
    return *this;
}

DiscreteMatrix::~DiscreteMatrix()
{
    delete m_d;
}

int DiscreteMatrix::rows() const
{
    return m_d->rows;
}

int DiscreteMatrix::columns() const
{
    return m_d->columns;
}

qsizetype DiscreteMatrix::count() const
{
    return m_d->rows * m_d->columns;
}

TableData DiscreteMatrix::at(int row, int column) const
{
    QReadLocker locker(&m_lock);
    const qsizetype i = m_d->index(row, column);
    const auto &[data, l] = m_d->data[shard(i)];
    QReadLocker dLocker(&l);
    return data.value(i, TableData());
}

bool DiscreteMatrix::setData(int row, int column, const TableData &data)
{
    QReadLocker locker(&m_lock);
    const qsizetype realIndex = m_d->index(row, column);
    if (realIndex == -1) {
        return false;
    }
    auto &[map, lock] = m_d->data[shard(realIndex)];
    QWriteLocker dataLocker(&lock);
    if (data == TableData()) {
        return map.remove(realIndex);
    }
    map[realIndex] = data;
    return true;
}

bool DiscreteMatrix::setData(int row, int column, TableData &&data)
{
    QReadLocker locker(&m_lock);
    const qsizetype realIndex = m_d->index(row, column);
    if (realIndex == -1) {
        return false;
    }
    auto &[map, lock] = m_d->data[shard(realIndex)];
    QWriteLocker dataLocker(&lock);
    if (data == TableData()) {
        return map.remove(realIndex);
    }
    map[realIndex] = std::move(data);
    return true;
}

bool DiscreteMatrix::insertColumns(const int column, const int count)
{
    QWriteLocker locker(&m_lock);
    if (column > m_d->columns || column < 0 || count < 1) {
        qWarning() << "Invalid column" << column << "or count" << count;
        return false;
    }
    auto &cache = m_d->invalidCache[COL_CACHE_INDEX];
    auto old = m_d->columns;
    m_d->columnIndexes.insert(column, count, -1);
    for (int idx{0}; idx < count; ++idx) {
        if (!cache.isEmpty()) {
            // 存在缓存
            m_d->columnIndexes[column + idx] = cache.dequeue();
            continue;
        }
        while (m_d->columnIndexes.contains(old)) {
            ++old;
        }
        m_d->columnIndexes[column + idx] = old;
    }
    m_d->columns += count;
    return true;
}

bool DiscreteMatrix::insertRows(const int row, const int count)
{
    QWriteLocker locker(&m_lock);
    if (row > m_d->rows || row < 0 || count < 1) {
        qWarning() << "row out of range";
        return false;
    }
    auto &cache = m_d->invalidCache[ROW_CACHE_INDEX];
    qsizetype old = m_d->rows;
    m_d->rowIndexes.insert(row, count, -1);
    for (int idx{0}; idx < count; ++idx) {
        if (!cache.isEmpty()) {
            // 存在缓存
            m_d->rowIndexes[row + idx] = cache.dequeue();
            continue;
        }
        while (m_d->rowIndexes.contains(old)) {
            ++old;
        }
        m_d->rowIndexes[row + idx] = old;
    }
    m_d->rows += count;
    return true;
}

bool DiscreteMatrix::removeColumns(const int column, const int count)
{
    QWriteLocker locker(&m_lock);
    if (column < 0 || column > m_d->columns || count < 1 || column + count > m_d->columns) {
        qWarning() << "column out of range";
        return false;
    }

    auto &cache = m_d->invalidCache[COL_CACHE_INDEX];
    // 删除数据及缓存索引
    QHash<qsizetype, QList<qsizetype>> removeIdxes;
    for (int idx{0}; idx < count; ++idx) {
        // 缓存索引
        cache.enqueue(m_d->columnIndexes[idx + column]);
        // 缓存删除数据索引
        for (int row{0}; row < m_d->rows; ++row) {
            const qsizetype i = m_d->index(row, idx + column);
            removeIdxes[shard(i)].append(i);
        }
    }
    // 多线程删除数据
    for (auto it = removeIdxes.begin(); it != removeIdxes.end(); ++it) {
        const qsizetype shard = it.key();
        const QList<qsizetype> &idxes = it.value();
        QThreadPool::globalInstance()->start([this, shard, idxes]() {
            auto &[data, lock] = m_d->data[shard];
            QWriteLocker dLocker(&lock);
            for (const qsizetype i : idxes) {
                (void) data.remove(i);
            }
            data.squeeze();
        });
    }
    // 删除索引
    m_d->columnIndexes.remove(column, count);
    m_d->columns -= count;

    return true;
}

bool DiscreteMatrix::removeRows(const int row, const int count)
{
    QWriteLocker locker(&m_lock);
    if (row < 0 || row > m_d->rows || count < 1 || row + count > m_d->rows) {
        qWarning() << "row out of range";
        return false;
    }
    auto &cache = m_d->invalidCache[ROW_CACHE_INDEX];
    // 删除数据及缓存索引
    QHash<qsizetype, QList<qsizetype>> removeIdxes;
    for (int idx{0}; idx < count; ++idx) {
        // 缓存索引
        cache.enqueue(m_d->rowIndexes[row + idx]);
        // 缓存删除数据索引
        for (int col{0}; col < m_d->columns; ++col) {
            const qsizetype i = m_d->index(row + idx, col);
            removeIdxes[shard(i)].append(i);
        }
    }
    // 多线程删除数据
    for (auto it = removeIdxes.begin(); it != removeIdxes.end(); ++it) {
        const qsizetype shard = it.key();
        const QList<qsizetype> &idxes = it.value();
        QThreadPool::globalInstance()->start([this, shard, idxes]() {
            auto &[data, lock] = m_d->data[shard];
            QWriteLocker dLocker(&lock);
            for (const qsizetype i : idxes) {
                (void) data.remove(i);
            }
            data.squeeze();
        });
    }
    // 删除索引
    m_d->rowIndexes.remove(row, count);
    m_d->rows -= count;
    return true;
}

