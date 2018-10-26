#include "heatmap.hpp"
#include <vector>
#include <limits>
#include <cmath>
#include <QDebug>
#include <QPainter>

Heatmap::Heatmap(const MultivariateFunction &f)
    : f_(f)
{}

static QColor blend(QColor a, QColor b, double t) {
    return QColor(int((1.-t)*a.red() + t*b.red()),
                  int((1.-t)*a.green() + t*b.green()),
                  int((1.-t)*a.blue() + t*b.blue()));
}

QImage Heatmap::render(Settings par)
{
    QImage heatmap(par.w, par.h, QImage::Format_RGB32);

    std::vector<std::vector<double>> values(par.w, std::vector<double>(par.h));

    double x_step = (par.x_max - par.x_min)/double(par.w);
    double y_step = (par.y_max - par.y_min)/double(par.h);

    double f_max = -std::numeric_limits<double>::infinity();
    double f_min =  std::numeric_limits<double>::infinity();

    for (int i = 0; i < par.w; ++i) {
        for (int j = 0; j < par.h; ++j) {
            double x = par.x_min + i * x_step;
            double y = par.y_min + j * y_step;

            values[i][j] = f_({x, y});

            f_max = std::max(f_max, values[i][j]);
            f_min = std::min(f_min, values[i][j]);
        }
    }

    for (int i = 0; i < par.w; ++i) {
        for (int j = 0; j < par.h; ++j) {
            double f = values[i][j];
            double f_ = (f - f_min)/(f_max - f_min);
            double t = f_/(par.scale_coeff + f_);

            double t_ = ceil(par.discretization_coeff*t)/par.discretization_coeff;

            QColor col = blend(par.color_low, par.color_high, t_);
            heatmap.setPixelColor(i, j, col);
        }
    }

    return heatmap.mirrored(false, true);
}
