/*
 * Author: Chen Shtar 318731411 & Lidor Ovadia 204268114
 */

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "minCircle.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>


struct correlatedFeatures{
    string feature1,feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    float radius = 0;
    Point center = Point(0,0);
};


class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    vector<correlatedFeatures> cf;
    float threshold;
public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    virtual correlatedFeatures createNewCorr(float cor, string f1, string f2, float *x, float *y, int size);
    virtual bool isDev(correlatedFeatures cPair, Point p);
    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel(){
        return cf;
    }
    void SetNewThreshold(float new_threshold);



};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
