#include "optimizationvizwidget.h"
#include "global.hpp"
#include "heatmap.hpp"
#include <QDebug>
#include <QMouseEvent>

OptimizationVizWidget::OptimizationVizWidget(QWidget* parent) {
    setParent(parent);
    setAlignment(Qt::AlignCenter);
}

void OptimizationVizWidget::paintEvent(QPaintEvent *e) {
    QLabel::paintEvent(e);

    auto& par = Global::get();

    int image_w = width();
    int image_h = height();

    double exp_w = par.ot.x_max - par.ot.x_min;
    double exp_h = par.ot.y_max - par.ot.y_min;

    if (image_w > image_h) {
        image_w = image_h / (exp_h/exp_w);
    } else {
        image_h = (exp_h/exp_w) * image_w;
    }

    if (size_changed_significantly(image_w, image_h)) {
        if (Global::get().ot.func) {
            setPixmap(QPixmap::fromImage(Heatmap::render(image_w, image_h)));
        }
        cur_image_h = image_h;
        cur_image_w = image_w;
    }
}

void OptimizationVizWidget::mouseReleaseEvent(QMouseEvent* e) {
    if (!click_inside_image(e->x(), e->y())) {
        return;
    }

    auto xy = image_coordinates(e->x(), e->y());

    auto& par = Global::get();

    int w = cur_image_w;
    int h = cur_image_h;

    double x_step = (par.ot.x_max - par.ot.x_min)/double(w);
    double y_step = (par.ot.y_max - par.ot.y_min)/double(h);

    double x = par.ot.x_min + xy.first * x_step;
    double y = par.ot.y_min + xy.second * y_step;

    emit pointTriggered(x, y);
}
