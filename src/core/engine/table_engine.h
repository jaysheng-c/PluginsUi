/**
  ********************************************************************************
  * @file           : table_engine.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/06/28
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef TABLE_ENGINE_H
#define TABLE_ENGINE_H

#include <QObject>
#include <QPointer>
#include "core/global.h"

class QAbstractItemModel;

namespace Plugins {

enum class FileFormat;
class FileImporterInterface;
class FileExporterInterface;

}

class CORE_EXPORT TableEngine final : public QObject {
    Q_OBJECT
signals:
    void progress(const QString &text, int value);
    void dataLoaded(bool success);
    void dataSaved(bool success);
public:
    explicit TableEngine(QObject *parent = nullptr);
    NODISCARD bool loadFromFile(const QString &path);
    NODISCARD bool saveToFile(const QString &path, Plugins::FileFormat format);

    NODISCARD QAbstractItemModel *dataModel() const;

    // 扩展接口
    void registerImporter(const QSharedPointer<Plugins::FileImporterInterface> &importer);
    void registerExporter(const QSharedPointer<Plugins::FileExporterInterface> &exporter);

private:
    QPointer<QAbstractItemModel> m_model;

    QVector<QSharedPointer<Plugins::FileImporterInterface>> m_importers;
    QVector<QSharedPointer<Plugins::FileExporterInterface>> m_exporters;
};


#endif //TABLE_ENGINE_H
