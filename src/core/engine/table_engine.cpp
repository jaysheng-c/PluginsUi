/**
  ********************************************************************************
  * @file           : table_engine.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/06/28
  * @version        : 1.0
  ********************************************************************************
  */

#include "table_engine.h"

#include <QAbstractItemModel>
#include <QFileInfo>

#include "plugins/plugin_interface.h"

using namespace Plugins;

namespace {

class FileFormater {
public:
    FileFormat operator()(const QString& path) const
    {
        const QString suffix = QFileInfo(path).suffix().toLower();
        if (suffix == "csv") return FileFormat::CSV;
        if (suffix == "txt") return FileFormat::TXT;
        if (suffix == "xlsx" || suffix == "xls") return FileFormat::Excel;
        return FileFormat::Unknown;
    }
};

}


TableEngine::TableEngine(QObject *parent)
    : QObject(parent)
{
}

bool TableEngine::loadFromFile(const QString &path)
{
    const auto format = FileFormater()(path);
    for (const auto& importer : m_importers) {
        if (importer->canHandle(format)) {
            if (auto *newModel = importer->import(path)) {
                if (!m_model.isNull()) m_model.data()->deleteLater();
                m_model = newModel;
                m_model->setParent(this);
                emit dataLoaded(true);
                return true;
            }
        }
    }
    qWarning() << "No importer found for" << path << "format" << format;
    emit dataLoaded(false);
    return false;
}

bool TableEngine::saveToFile(const QString &path, const FileFormat format)
{
    if (m_model.isNull()) {
        return false;
    }
    for (const auto &exporter : m_exporters) {
        if (exporter->canHandle(format)) {
            const bool success = exporter->exportModel(m_model.data(), path);
            emit dataSaved(success);
            return success;
        }
    }
    qWarning() << "No exporter found for formater" << format;
    emit dataSaved(false);
    return false;
}

QAbstractItemModel *TableEngine::dataModel() const
{
    return m_model.data();
}

void TableEngine::registerImporter(const QSharedPointer<FileImporterInterface> &importer)
{
    if (importer && !m_importers.contains(importer)) {
        m_importers.append(importer);
    }
}

void TableEngine::registerExporter(const QSharedPointer<FileExporterInterface> &exporter)
{
    if (exporter && !m_exporters.contains(exporter)) {
        m_exporters.append(exporter);
    }
}
