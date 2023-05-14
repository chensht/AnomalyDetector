/*
 * Author: Chen Shtar 318731411 & Lidor Ovadia 204268114
 */

#include "SimpleAnomalyDetector.h"
#include <vector>
#include <map>
#include <string>
#include <math.h>
using namespace std;


SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TODO Auto-generated constructor stub
}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TODO Auto-generated destructor stub
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    // TODO Auto-generated destructor stub
    map<string, vector<float>> tempMap;
    tempMap = ts.getDataSet();
    string feature1;
    string feature2;
    float tempPearson = 0;
    float maxCor = 0;
    const int size = ts.getDataSet().begin()->second.size();
    float first[size];
    float second[size];
    float bestFirst[size];
    float bestSecond[size];
    for (auto const &f1: ts.getDataSet()) {
        feature1 = f1.first;
        tempPearson = 0;
        maxCor = 0;
        tempMap.erase(tempMap.begin());
        if (tempMap.size() == 0) {
            return;
        }
        for (auto const &f2: tempMap) {
            tempPearson = 0;
            if (f1.first != f2.first) {
                for (int i = 0; i < size; i++) {
                    first[i] = f1.second[i];
                    second[i] = f2.second[i];
                }
                tempPearson = fabs(pearson(first, second, size));
                if (tempPearson > maxCor) {
                    maxCor = tempPearson;
                    feature2 = f2.first;
                }
            }
        }
        for (int j = 0; j < size; j++) {
            bestFirst[j] = ts.getValues(feature1)[j];
            bestSecond[j] = ts.getValues(feature2)[j];
        }
        if (maxCor >= 0.5) {
            correlatedFeatures c = createNewCorr(maxCor, feature1, feature2, bestFirst, bestSecond, size);
            cf.push_back(c);
        }
    }
}


vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts){
    // TODO Auto-generated destructor stub
    vector<AnomalyReport> ar;
    for (correlatedFeatures c: cf) {
        string feature1 = c.feature1;
        string feature2 = c.feature2;
        vector<float> values1 = ts.getValues(feature1);
        vector<float> values2 = ts.getValues(feature2);
        int size = values1.size();
        for (int i = 0; i < size; i++) {
            float x = values1[i];
            float y = values2[i];
            Point point(x, y);
            if (isDev(c,point)) {
                string des = c.feature1 + "-" + c.feature2;
                long step = i + 1;
                AnomalyReport a(des, step);
                ar.push_back(a);
            }
        }
    }
    return ar;
}

correlatedFeatures SimpleAnomalyDetector::createNewCorr(float cor, string f1, string f2, float *x, float *y, int size){
    float tempDeviation = 0;
    correlatedFeatures c;
    c.feature1 = f1;
    c.feature2 = f2;
    c.corrlation = cor;
    c.lin_reg = linear_reg(x, y, size);
    c.threshold = 0;
    for (int k = 0; k < size; k++){
        Point p(x[k], y[k]);
        tempDeviation = dev(p, c.lin_reg);
        if (tempDeviation > c.threshold){
            c.threshold = tempDeviation;
        }
    }
    c.threshold = c.threshold * 1.1;
    return c;
}

bool SimpleAnomalyDetector::isDev(correlatedFeatures cPair, Point p) {
    float deviation = dev(p, cPair.lin_reg);
    if (deviation > cPair.threshold) {
        return true;
    }
    else {
        return false;
    }
}
void SimpleAnomalyDetector::SetNewThreshold(float new_threshold){
    this->threshold = new_threshold;
}