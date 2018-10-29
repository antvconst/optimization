#pragma once

#include <QLabel>
#include <QPainter>
#include "global.hpp"
#include "basic/point.hpp"

#include <QDebug>

class OptimizationVizWidget : public QLabel
{
    Q_OBJECT
public:
    OptimizationVizWidget(QWidget*);
    virtual ~OptimizationVizWidget() {}

    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);

    void render(const OptimizationPath& path);

signals:
    void pointTriggered(double x, double y);

private:
    QImage clear_heatmap;
    OptimizationPath path;
    int cur_image_h;
    int cur_image_w;

    inline bool size_changed_significantly(int, int h) {
        return double(cur_image_h) / h < 0.8 || double(h) / cur_image_h < 0.8;
    }

    inline bool click_inside_image(int x, int y) {
        int c_x = width()/2;
        int c_y = height()/2;

        return (c_x - cur_image_w/2 <= x &&
                x <= c_x + cur_image_w/2 &&
                c_y - cur_image_h/2 <= y &&
                y <= c_y + cur_image_h/2);
    }

    inline std::pair<int, int> coord_label_to_image(int x, int y) {
        int origin_x = (width()-cur_image_w)/2;
        int origin_y = (height()-cur_image_h)/2;

        return {x-origin_x, cur_image_h-(y-origin_y)};
    }

    inline std::pair<double, double> coord_image_to_real(int x, int y) {
        auto& par = Globals::get();

        int w = cur_image_w;
        int h = cur_image_h;

        double x_step = (par.ot.x_max - par.ot.x_min)/double(w);
        double y_step = (par.ot.y_max - par.ot.y_min)/double(h);

        double x_real = par.ot.x_min + x * x_step;
        double y_real = par.ot.y_min + y * y_step;

        return {x_real, y_real};
    }

    inline std::pair<int, int> coord_real_to_image(double x, double y) {
        auto& par = Globals::get();

        int w = cur_image_w;
        int h = cur_image_h;

        double x_step = (par.ot.x_max - par.ot.x_min)/double(w);
        double y_step = (par.ot.y_max - par.ot.y_min)/double(h);

        int x_im = (x - par.ot.x_min)/x_step;
        int y_im = (y - par.ot.y_min)/y_step;

        return {x_im, cur_image_h - y_im};
    }

    inline void draw_point(QPainter& painter, double x, double y) {
        auto coord_img = coord_real_to_image(x, y);

        painter.drawPoint(coord_img.first, coord_img.second);
    }

    inline void draw_point(QPainter& painter, const Point& p) {
        draw_point(painter, p[0], p[1]);
    }

    void render_heatmap(int w, int h);
};
