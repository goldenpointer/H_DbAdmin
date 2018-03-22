#include "HDbAdminWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HDbAdminWindow w;
    w.show();

    return a.exec();
}
