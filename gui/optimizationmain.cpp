#include "optimizationmain.hpp"
#include "ui_optimizationmain.h"
#include "heatmap.hpp"

#include <QPixmap>
#include <QColor>

OptimizationMain::OptimizationMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OptimizationMain)
{
    ui->setupUi(this);

    auto f = [](const Point& v) {
        return (1 - v[0])*(1 - v[0]) + 100*(v[1] - v[0]*v[0])*(v[1] - v[0]*v[0]);
    };

    Heatmap hm(f);
    auto par = Heatmap::Settings {
            1000, 1000,
            -2, 2,
            -2, 2,
            30, 0.008,
            QColor("white"), QColor("navy")
    };

    ui->label->setPixmap(QPixmap::fromImage(hm.render(par)));
    ui->label->setAlignment(Qt::AlignCenter);
}

OptimizationMain::~OptimizationMain()
{
    delete ui;
}
