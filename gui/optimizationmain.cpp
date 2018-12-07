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
#include <QSlider>
#include <QMessageBox>

#include "exprtk/exprtk_wrapper.hpp"

OptimizationMain::OptimizationMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OptimizationMain),
    ready_(false)
{
    ui->setupUi(this);

    setup();

    auto& par = Globals::get();

    connect(ui->opt_viz, &OptimizationVizWidget::pointTriggered, [&](double x, double y) {
        if (!ready_) {
            QMessageBox::critical(this, "Error", "Not ready");
            return;
        }

        AABoxRegion box({{par.ot.x_min, par.ot.x_max},
                         {par.ot.y_min, par.ot.y_max}});

        auto path = par.om.optimizer->minimize(par.ot.func, box, {x, y}, par.om.stopping_criteria);
        ui->opt_viz->set_path(path);
        ui->opt_viz->render();

        double x_opt = path.back().first[0];
        double y_opt = path.back().first[1];
        double f_opt = path.back().second;
        ui->resultsLabel->setText(QString("Optimum point:  (%1, %2)\nFunction value: %3\nConverged in %4 successful iterations").arg(x_opt).arg(y_opt).arg(f_opt).arg(path.size()));
    });

    connect(ui->opt_viz, &OptimizationVizWidget::pointHovered, [&](double x, double y) {
        ui->statusBar->showMessage(QString("Point: (%1, %2)").arg(x).arg(y));
    });

    connect(ui->scaleSlider, &QSlider::valueChanged, [&](int t) {
       Globals::get_mutable().hm.scale_coeff = 0.01 * t;
       ui->opt_viz->render(true);
    });

    connect(ui->applyButton, &QPushButton::clicked, this, &OptimizationMain::setup);
}

void OptimizationMain::setup()
{
    ready_ = false;
    ui->opt_viz->set_ready(false);

    auto& par = Globals::get_mutable();

    auto new_func = ExprTK_Function(ui->target_func_textEdit->toPlainText().toStdString());

    if (!new_func) {
        QMessageBox::critical(this, "Error", "Failed to parse the function. Falling back.");
        return;
    }

    par.ot.func = new_func;

    // let's leave these hardcoded
    par.hm.discretization_coeff = 30;
    par.hm.color_low = QColor("white");
    par.hm.color_high = QColor("navy");

    par.hm.scale_coeff = 0.01 * ui->scaleSlider->value();

    par.ot.x_min = ui->x_min_spinBox->value();
    par.ot.x_max = ui->x_max_spinBox->value();
    par.ot.y_min = ui->y_min_spinBox->value();
    par.ot.y_max = ui->y_max_spinBox->value();

    if (par.ot.x_min >= par.ot.x_max || par.ot.y_min >= par.ot.y_max) {
        QMessageBox::critical(this, "Error", "Invalid region boundaries.");
        return;
    }

    StoppingCriteria sc;

    if (ui->max_iter_checkBox->isChecked()) {
        sc.add<MaxIterations>(ui->max_iter_spinBox->value());
    }
    if (ui->max_failed_iter_checkBox->isChecked()) {
        sc.add<MaxFailedIterations>(ui->max_failed_iter_spinBox->value());
    }
    if (ui->point_proximity_checkBox->isChecked()) {
        double pp = pow(0.1, ui->point_proximity_spinBox->value());
        sc.add<PointProximity>(pp);
    }
    if (ui->value_proximity_checkBox->isChecked()) {
        double vp = pow(0.1, ui->value_proximity_spinBox->value());
        sc.add<ValueProximity>(vp);
    }
    par.om.stopping_criteria = std::move(sc);

    QString method = ui->method_comboBox->currentText();
    if (method == "Stochastic Search") {
        double p = ui->p_spinBox->value();
        par.om.optimizer.reset(new StochasticSearch(p));
    }
    else if (method == "Gradient Descent") {
        double rate = pow(0.1, ui->optrate_spinBox->value());
        par.om.optimizer.reset(new GradientDescent(rate));
    }

    ui->opt_viz->set_path({});
    ui->resultsLabel->setText("");

    ready_ = true;
    ui->opt_viz->set_ready(true);

    ui->opt_viz->render(true);
}

OptimizationMain::~OptimizationMain()
{
    delete ui;
}
