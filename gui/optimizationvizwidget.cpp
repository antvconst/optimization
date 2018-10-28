#include "optimizationvizwidget.h"
#include "global.hpp"
#include "heatmap.hpp"
#include <QDebug>

OptimizationVizWidget::OptimizationVizWidget(QWidget* parent) {
    setParent(parent);
    setAlignment(Qt::AlignCenter);
}

void OptimizationVizWidget::paintEvent(QPaintEvent *e) {
    QLabel::paintEvent(e);

    auto& par = Global::get();

    int w = width();
    int h = height();

    double exp_w = par.ot.x_max - par.ot.x_min;
    double exp_h = par.ot.y_max - par.ot.y_min;

    if (w > h) {
        w = h / (exp_h/exp_w);
    } else {
        h = (exp_h/exp_w) * w;
    }

    if (Global::get().ot.func) {
        setPixmap(QPixmap::fromImage(Heatmap::render(w, h)));
    }
}
