#include "des8ui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DES8UI w;
    w.show();

    return a.exec();
}
