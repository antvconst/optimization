#include "exprtk/exprtk_wrapper.hpp"

ExprTK_Function::ExprTK_Function(const std::string &func_str)
    : func_str_(func_str), x_proxy(0), y_proxy(0) {
    compile();
}

ExprTK_Function::ExprTK_Function(const ExprTK_Function &other)
    : func_str_(other.func_str_), x_proxy(0), y_proxy(0) {
    compile();
}

ExprTK_Function::ExprTK_Function(ExprTK_Function &&other)
    : func_str_(other.func_str_), x_proxy(0), y_proxy(0) {
    compile();
}

ExprTK_Function& ExprTK_Function::operator=(const ExprTK_Function &other) {
    func_str_ = other.func_str_;
    recompile();

    return *this;
}

ExprTK_Function& ExprTK_Function::operator=(ExprTK_Function &&other) {
    func_str_ = other.func_str_;
    recompile();

    return *this;
}

void ExprTK_Function::compile() {
    symbol_table.add_variable("x", x_proxy);
    symbol_table.add_variable("y", y_proxy);
    expr.register_symbol_table(symbol_table);

    exprtk::parser<double> parser;
    parser.compile(func_str_, expr);
}

void ExprTK_Function::recompile() {
    symbol_table.clear();
    expr.release();
    compile();
}

double ExprTK_Function::operator()(const Point &p) {
    x_proxy = p[0];
    y_proxy = p[1];

    return expr.value();
}

double ExprTK_Function::operator()(double x, double y) {
    x_proxy = x;
    y_proxy = y;

    return expr.value();
}
