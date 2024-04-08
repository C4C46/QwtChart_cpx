#include "ChartDemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChartDemo w;
    w.show();
    return a.exec();
}
