#include "optimizationmain.hpp"
#include "ui_optimizationmain.h"
#include "heatmap.hpp"

#include <QPixmap>
#include <QColor>

#include "exprtk/exprtk_wrapper.hpp"

OptimizationMain::OptimizationMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OptimizationMain)
{
    ui->setupUi(this);

    auto f = ExprTK_Function("(1-x)^2 + 100*(y - x^2)^2");

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
