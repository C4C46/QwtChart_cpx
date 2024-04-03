#include "ChartDemo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChartDemo w;
    w.show();
    return a.exec();
}
