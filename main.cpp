#include <QApplication>
#include "src/ui/public/loader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UiLoader loader;
    loader.show();

    return QApplication::exec();
}