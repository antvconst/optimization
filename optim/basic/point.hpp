#pragma once

#include <iostream>
#include <vector>
#include <initializer_list>

const double EPS = 10e-9;

class Point
{
    const size_t N_;
    std::vector<double> data_;

public:
    Point() = delete;

    Point(const Point& other) = default;
    Point(Point&& other) = default;

    /**
     * @brief Construct a new Point object
     * 
     * @param N Dimensionality
     */
    Point(size_t N);
    Point(const std::vector<double>& data);
    Point(std::initializer_list<double> values);
    ~Point() = default;

    /**
     * @brief Dimensionality of point
     * 
     * @return size_t Dimensionality
     */
    size_t dim() const;

    /**
     * @brief Length of radius vector for point
     * 
     * @return double Length
     */
    double len() const;

    /**
     * @brief Return new point of dimensionality N with coordinates p_j = [i == j].
     * 
     * @param N 
     * @param i 
     * @return Point 
     */
    static Point unit(size_t N, size_t i);
    
    double operator[](size_t i) const;
    double& operator[](size_t i);
    Point& operator= (const Point& other);

    friend bool operator== (const Point& lhs, const Point& rhs);
    friend bool operator!= (const Point& lhs, const Point& rhs);
    friend Point operator- (const Point& vec);
    friend Point operator+ (const Point& lhs, const Point& rhs);
    friend Point operator- (const Point& lhs, const Point& rhs);
    friend Point operator* (const Point& lhs, const Point& rhs);
    friend Point operator* (const Point& vec, double alpha);
    friend Point operator* (double alpha, const Point& vec);
    friend Point operator/ (const Point& vec, double alpha);

    /**
     * @brief Pretty print point into output stream
     * 
     * @param os Output stream
     * @param p Point
     * @return std::ostream& 
     */
    friend std::ostream& operator << (std::ostream& os, const Point& p);
};