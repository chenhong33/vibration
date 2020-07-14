#include "bt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BT w;
    w.show();
    return a.exec();
}
