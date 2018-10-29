#pragma once

#include <QLabel>

#include "heatmap.hpp"

class OptimizationVizWidget : public QLabel
{
    Q_OBJECT
public:
    OptimizationVizWidget(QWidget*);
    virtual ~OptimizationVizWidget() {}

    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent*);

signals:
    void pointTriggered(double x, double y);

private:
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

    inline std::pair<int, int> image_coordinates(int x, int y) {
        int origin_x = (width()-cur_image_w)/2;
        int origin_y = (height()-cur_image_h)/2;

        return {x-origin_x, cur_image_h-(y-origin_y)};
    }
};
