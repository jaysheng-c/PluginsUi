/**
  ********************************************************************************
  * @file           : excel_import.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/06/29
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef EXCEL_IMPORTER_H
#define EXCEL_IMPORTER_H

#include "macro.h"

#include "plugins/plugin_interface.h"

namespace Plugins {

class ExcelImporter : public FileImporterInterface {
public:
    explicit ExcelImporter() = default;
    NODISCARD bool canHandle(FileFormat format) const override;
    QAbstractItemModel* import(const QString& path) override;
};

}


#endif //EXCEL_IMPORTER_H
