#include "public/loader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UiLoader loader;
    loader.show();

    return QApplication::exec();
}