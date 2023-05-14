/*
 * Author: Chen Shtar 318731411 & Lidor Ovadia 204268114
 */

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
    HybridAnomalyDetector();
    virtual ~HybridAnomalyDetector();
    correlatedFeatures createNewCorr(float cor, string f1, string f2, float *x, float *y, int size);
    bool isDev(correlatedFeatures cPair, Point p);


};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
