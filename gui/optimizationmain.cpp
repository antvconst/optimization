#include "optimizationmain.hpp"
#include "ui_optimizationmain.h"
#include "optimizationvizwidget.h"
#include "global.hpp"

#include <QPixmap>
#include <QColor>
#include <QDebug>

#include "exprtk/exprtk_wrapper.hpp"

OptimizationMain::OptimizationMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OptimizationMain)
{
    ui->setupUi(this);

    auto f = ExprTK_Function("(1-x)^2 + 100*(y - x^2)^2");

    auto& par = Globals::get_mutable();
    par.hm.discretization_coeff = 30;
    par.hm.scale_coeff = 0.008;
    par.hm.color_low = QColor("white");
    par.hm.color_high = QColor("navy");

    par.ot.x_min = -1;
    par.ot.x_max = 3;
    par.ot.y_min = -2;
    par.ot.y_max = 2;

    par.ot.func = f;

    connect(ui->label, &OptimizationVizWidget::pointTriggered, [](double x, double y) { qDebug() << x << " " << y; });
}

OptimizationMain::~OptimizationMain()
{
    delete ui;
}
