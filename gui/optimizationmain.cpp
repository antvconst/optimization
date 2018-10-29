#include "optimizationmain.hpp"
#include "ui_optimizationmain.h"
#include "optimizationvizwidget.h"
#include "global.hpp"
#include "optimization/stochastic_search.hpp"
#include "optimization/gradient_descent.hpp"
#include "basic/aaboxregion.hpp"
#include "optimization/stopping_criteria.hpp"

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

    connect(ui->label, &OptimizationVizWidget::pointTriggered, [&](double x, double y) {
        AABoxRegion box({{par.ot.x_min, par.ot.x_max},
                         {par.ot.y_min, par.ot.y_max}});
        StoppingCriteria sc;
        sc.add<MaxIterations>(100000);
        par.om.optimizer.reset(new GradientDescent());
        auto path = par.om.optimizer->minimize(par.ot.func, box, {x, y}, sc);
        qDebug() << "path length: " << path.size();
        ui->label->render(path);
    });
}

OptimizationMain::~OptimizationMain()
{
    delete ui;
}
