/*
 * Author: Chen Shtar 318731411 & Lidor Ovadia 204268114
 */

#include <iostream>
#include <cmath>
#include "anomaly_detection_util.h"
using namespace std;

 // returns the expectation of X
float avg(float* x, int size) {
    float avg = 0;
    float sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += x[i];
    }
    avg = sum / size;
    return avg;
}

// returns the variance of X and Y
float var(float* x, int size) {
    float var = 0;
    float exp = avg(x, size);
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += pow(x[i] - exp, 2.0);
    }
    var = sum / size;
    return var;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size) {
    float x_avg = avg(x, size);
    float y_avg = avg(y, size);
    float cov = 0;
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += (x[i] - x_avg) * (y[i] - y_avg);
    }
    cov = sum / size;
    return cov;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size) {
    float covA = cov(x, y, size);
    float sigX = sqrt(var(x, size));
    float sigY = sqrt(var(y, size));
    float pearson = covA / (sigX * sigY);
    return pearson;
}


// performs a linear regression and return s the line equation
Line linear_reg(Point** points, int size) {
    float* x = new float[size];
    float* y = new float[size];

    for (int i = 0; i < size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    float a = 0, b = 0;
    a = cov(x, y, size) / var(x, size);
    b = avg(y, size) - (a * avg(x, size));
    delete[] x;
    delete[] y;
    return Line(a, b);
}

// performs a linear regression and return s the line equation
Line linear_reg(float* x, float* y, int size) {
   float a = 0, b = 0;
    a = cov(x, y, size) / var(x, size);
    b = avg(y, size) - (a * avg(x, size));
    return Line(a, b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point** points, int size) {
    Line line = linear_reg(points, size);
    double f_x = (line.a * p.x) + line.b;
    double dev1 = std::abs(p.y - f_x);
    return dev1;
}

// returns the deviation between point p and the line
float dev(Point p, Line l) {
    double f_x = (p.x * l.a) + l.b;
    double dev1 = std::abs(f_x - p.y);
    return dev1;
}
