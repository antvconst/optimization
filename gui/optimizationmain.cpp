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
#include <QSlider>

#include "exprtk/exprtk_wrapper.hpp"

OptimizationMain::OptimizationMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OptimizationMain)
{
    ui->setupUi(this);

    setup();

    auto& par = Globals::get();

    connect(ui->opt_viz, &OptimizationVizWidget::pointTriggered, [&](double x, double y) {
        AABoxRegion box({{par.ot.x_min, par.ot.x_max},
                         {par.ot.y_min, par.ot.y_max}});

        auto path = par.om.optimizer->minimize(par.ot.func, box, {x, y}, par.om.stopping_criteria);
        qDebug() << "path length: " << path.size();
        ui->opt_viz->set_path(path);
        ui->opt_viz->render();

        double x_opt = path.back().first[0];
        double y_opt = path.back().first[1];
        double f_opt = path.back().second;
        ui->resultsLabel->setText(QString("Optimum point:  (%1, %2)\nFunction value: %3\n").arg(x_opt).arg(y_opt).arg(f_opt));
    });

    connect(ui->opt_viz, &OptimizationVizWidget::pointHovered, [&](double x, double y) {
        ui->statusBar->showMessage(QString("Point: (%1, %2)").arg(x).arg(y));
    });

    connect(ui->scaleSlider, &QSlider::valueChanged, [&](int t) {
       qDebug() << t;
       Globals::get_mutable().hm.scale_coeff = 0.01 * t;
       ui->opt_viz->render(true);
    });

    connect(ui->applyButton, &QPushButton::clicked, this, &OptimizationMain::setup);
}

void OptimizationMain::setup()
{
    auto& par = Globals::get_mutable();

    // let's leave these hardcoded
    par.hm.discretization_coeff = 30;
    par.hm.color_low = QColor("white");
    par.hm.color_high = QColor("navy");

    par.hm.scale_coeff = 0.01 * ui->scaleSlider->value();

    par.ot.x_min = ui->x_min_spinBox->value();
    par.ot.x_max = ui->x_max_spinBox->value();
    par.ot.y_min = ui->y_min_spinBox->value();
    par.ot.y_max = ui->y_max_spinBox->value();
    par.ot.func = ExprTK_Function(ui->target_func_textEdit->toPlainText().toStdString());

    StoppingCriteria sc;

    if (ui->max_iter_checkBox->isChecked()) {
        sc.add<MaxIterations>(ui->max_iter_spinBox->value());
    }
    if (ui->max_failed_iter_checkBox->isChecked()) {
        sc.add<MaxFailedIterations>(ui->max_failed_iter_spinBox->value());
    }
    if (ui->point_proximity_checkBox->isChecked()) {
        double pp = pow(0.1, ui->point_proximity_spinBox->value());
        qDebug() << pp;
        sc.add<PointProximity>(pp);
    }
    if (ui->value_proximity_checkBox->isChecked()) {
        double vp = pow(0.1, ui->value_proximity_spinBox->value());
        qDebug() << vp;
        sc.add<ValueProximity>(vp);
    }
    par.om.stopping_criteria = std::move(sc);

    QString method = ui->method_comboBox->currentText();
    qDebug() << method;
    if (method == "Stochastic Search") {
        double p = ui->p_spinBox->value();
        par.om.optimizer.reset(new StochasticSearch(p));
    }
    else if (method == "Gradient Descent") {
        par.om.optimizer.reset(new GradientDescent());
    }

    ui->opt_viz->set_path({});
    ui->resultsLabel->setText("");

    ui->opt_viz->render(true);
}

OptimizationMain::~OptimizationMain()
{
    delete ui;
}
