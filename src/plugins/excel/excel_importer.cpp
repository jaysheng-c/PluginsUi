/**
  ********************************************************************************
  * @file           : excel_import.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/06/29
  * @version        : 1.0
  ********************************************************************************
  */

#include "excel_importer.h"

#include <QStandardItem>

#include "QXlsx/QXlsx/header/xlsxdocument.h"

namespace Plugins {

bool ExcelImporter::canHandle(const FileFormat format) const
{
    return format == FileFormat::Excel;
}

QAbstractItemModel *ExcelImporter::import(const QString &path)
{
    const QXlsx::Document document(path);
    if (!document.load()) {
        return nullptr;
    }
    const auto sheetName = document.sheetNames().first();
    const auto *sheet = dynamic_cast<QXlsx::Worksheet*>(document.sheet(sheetName));
    const auto endCell = sheet->dimension().bottomRight();

    auto *model = new QStandardItemModel();

    model->setRowCount(endCell.row());
    model->setColumnCount(endCell.column());
    for (int row = 0; row <= endCell.row(); ++row) {
        for (int col = 0; col <= endCell.column(); ++col) {
            const auto &var = sheet->read(row + 1, col + 1);
            model->setData(model->index(row, col), var);
        }
    }

    return model;
}

}