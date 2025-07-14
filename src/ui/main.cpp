#include "public/loader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UiLoader::instance()->show();

    return QApplication::exec();
}