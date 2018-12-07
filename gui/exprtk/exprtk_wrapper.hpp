#pragma once

#include "exprtk.hpp"
#include "basic/point.hpp"

class ExprTK_Function {
    std::string func_str_;
    exprtk::symbol_table<double> symbol_table;
    exprtk::expression<double> expr;
    double x_proxy, y_proxy;
    bool ok;

protected:
    void compile();
    void recompile();

public:
    ExprTK_Function();
    ExprTK_Function(const std::string& func_str);
    ExprTK_Function(const ExprTK_Function& other);
    ExprTK_Function(ExprTK_Function&& other);

    ExprTK_Function& operator=(const ExprTK_Function& other);
    ExprTK_Function& operator=(ExprTK_Function&& other);

    operator bool() const;

    double operator() (double x, double y);
    double operator() (const Point& p);
};
