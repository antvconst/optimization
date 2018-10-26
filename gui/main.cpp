#include "optimizationmain.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OptimizationMain w;
    w.show();

    return a.exec();
}
