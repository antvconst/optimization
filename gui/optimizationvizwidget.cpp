#include "optimizationvizwidget.h"
#include "global.hpp"
#include <vector>
#include <limits>
#include <cmath>
#include <QDebug>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QPainterPath>

static QColor blend(QColor a, QColor b, double t) {
    return QColor(int((1.-t)*a.red() + t*b.red()),
                  int((1.-t)*a.green() + t*b.green()),
                  int((1.-t)*a.blue() + t*b.blue()));
}

OptimizationVizWidget::OptimizationVizWidget(QWidget* parent)
{
    setParent(parent);
    setAlignment(Qt::AlignCenter);
}

void OptimizationVizWidget::paintEvent(QPaintEvent *e) {
    QLabel::paintEvent(e);

    render(path);
}

void OptimizationVizWidget::mouseReleaseEvent(QMouseEvent* e) {
    if (!click_inside_image(e->x(), e->y())) {
        return;
    }

    auto xy = coord_label_to_image(e->x(), e->y());

    double x, y;
    std::tie(x, y) = coord_image_to_real(xy.first, xy.second);

    emit pointTriggered(x, y);
}

void OptimizationVizWidget::render_heatmap(int w, int h)
{
    clear_heatmap = QImage(w, h, QImage::Format_RGB32);

    auto& par = Globals::get();

    std::vector<std::vector<double>> values(w, std::vector<double>(h));

    double f_max = -std::numeric_limits<double>::infinity();
    double f_min =  std::numeric_limits<double>::infinity();

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            double x, y;
            std::tie(x, y) = coord_image_to_real(i, j);

            values[i][j] = par.ot.func({x, y});

            f_max = std::max(f_max, values[i][j]);
            f_min = std::min(f_min, values[i][j]);
        }
    }

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            double f = values[i][j];
            double f_ = (f - f_min)/(f_max - f_min);
            double t = f_/(par.hm.scale_coeff + f_);

            double t_ = ceil(par.hm.discretization_coeff*t)/par.hm.discretization_coeff;

            QColor col = blend(par.hm.color_low, par.hm.color_high, t_);
            clear_heatmap.setPixelColor(i, j, col);
        }
    }

    clear_heatmap = clear_heatmap.mirrored(false, true);
}

void OptimizationVizWidget::render(const OptimizationPath& path)
{
    this->path = path;
    auto& par = Globals::get();

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
        cur_image_h = image_h;
        cur_image_w = image_w;
        if (Globals::get().ot.func) {
            render_heatmap(image_w, image_h);
        }
    }

    QImage heatmap(clear_heatmap.copy());

    QPainter painter(&heatmap);
    painter.setPen(QPen(QBrush(Qt::red), 4, Qt::SolidLine, Qt::RoundCap));
    for (auto p : path) {
        draw_point(painter, p.first);
    }

    setPixmap(QPixmap::fromImage(heatmap));
}
