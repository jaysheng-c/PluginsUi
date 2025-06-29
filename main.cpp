#include <QApplication>
#include <QSharedPointer>
#include <QTableView>

#include "src/core/engine/table_engine.h"
#include "src/plugins/excel/excel_importer.h"
#include "src/ui/main_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto w = new MainWindow;
    w->show();

    auto *engine = new TableEngine(w);
    engine->registerImporter(QSharedPointer<Plugins::FileImporterInterface>(new Plugins::ExcelImporter()));

    (void) QObject::connect(engine, &TableEngine::dataLoaded, [engine, w](const bool success) {
        if (success) {
            auto *tableView = new QTableView(w);
            tableView->setModel(engine->dataModel());
            w->setCentralWidget(tableView);
        }
    });

    qDebug() << engine->loadFromFile("D:/workspace/PluginsUi/test_data/datasets.xlsx");



    return QApplication::exec();
}