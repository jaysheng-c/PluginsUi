/**
  ********************************************************************************
  * @file           : plugin_interface.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/06/28
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#include <QObject>
#include "macro.h"

class QAbstractItemModel;

namespace Plugins {
Q_NAMESPACE

enum class FileFormat {
    Unknown,
    Excel,
    CSV,
    TXT,
    CustomBinary
};
Q_DECLARE_FLAGS(FileFormats, FileFormat)
Q_DECLARE_OPERATORS_FOR_FLAGS(FileFormats)
Q_ENUM_NS(FileFormat)

// 文件导入器接口
class FileImporterInterface : public QObject {
public:
    NODISCARD virtual bool canHandle(FileFormat format) const = 0;
    virtual QAbstractItemModel* import(const QString& path) = 0;
};

// 文件导出器接口
class FileExporterInterface : public QObject {
public:
    NODISCARD virtual bool canHandle(FileFormat format) const = 0;
    virtual bool exportModel(QAbstractItemModel* model, const QString& path) = 0;
};

}


#endif //PLUGIN_INTERFACE_H
