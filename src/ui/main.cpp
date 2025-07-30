#include <QApplication>

#include "public/loader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UiLoader::instance()->show();

    return QApplication::exec();
}