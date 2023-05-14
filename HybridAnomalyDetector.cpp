/*
 * Author: Chen Shtar 318731411 & Lidor Ovadia 204268114
 */

#include "HybridAnomalyDetector.h"

HybridAnomalyDetector::HybridAnomalyDetector() {
    // TODO Auto-generated constructor stub

}

HybridAnomalyDetector::~HybridAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

correlatedFeatures HybridAnomalyDetector::createNewCorr(float cor, string f1, string f2, float *x, float *y, int size){
    if (cor >= 0.5 && cor < 0.9) {
        correlatedFeatures c;
        c.feature1 = f1;
        c.feature2 = f2;
        c.corrlation = cor;
        c.lin_reg = linear_reg(x, y, size);
        c.threshold = 0;
        Point* points [size];
        for (int k = 0; k < size; k++){
            points[k] = new Point(x[k], y[k]);
        }
        Circle c1 = findMinCircle(points, size);
        c.center = c1.center;
        c.radius = c1.radius * 1.1;
        c.threshold = c.radius;
        return c;
    }
    else {
        return SimpleAnomalyDetector::createNewCorr(cor, f1, f2, x, y, size);
    }
}

bool HybridAnomalyDetector::isDev(correlatedFeatures cPair, Point p) {
    if (cPair.corrlation >= 0.5 && cPair.corrlation < 0.9) {
        Circle c(cPair.center, cPair.threshold);
        if (!is_inside(c, p)){
            return true;
        }
        else{
            return false;
        }
    }
    else if ( cPair.corrlation >= 0.9){
        return SimpleAnomalyDetector::isDev(cPair, p);
    }
}