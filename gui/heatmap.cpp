#include "heatmap.hpp"
#include <vector>
#include <limits>
#include <cmath>
#include <QDebug>
#include <QPainter>

#include "global.hpp"

static QColor blend(QColor a, QColor b, double t) {
    return QColor(int((1.-t)*a.red() + t*b.red()),
                  int((1.-t)*a.green() + t*b.green()),
                  int((1.-t)*a.blue() + t*b.blue()));
}

QImage Heatmap::render(int w, int h)
{
    QImage heatmap(w, h, QImage::Format_RGB32);

    auto& par = Global::get();

    std::vector<std::vector<double>> values(w, std::vector<double>(h));

    double x_step = (par.ot.x_max - par.ot.x_min)/double(w);
    double y_step = (par.ot.y_max - par.ot.y_min)/double(h);

    double f_max = -std::numeric_limits<double>::infinity();
    double f_min =  std::numeric_limits<double>::infinity();

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            double x = par.ot.x_min + i * x_step;
            double y = par.ot.y_min + j * y_step;

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
            heatmap.setPixelColor(i, j, col);
        }
    }

    return heatmap.mirrored(false, true);
}
