

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "anomaly_detection_util.h"
#include "SimpleAnomalyDetector.h"
#include <cmath>
using namespace std;
/*

int main() {
    map<string , vector<float>> tempMap;
    map<string , vector<float>> map;
    map ["Time"] = {0.1, 0.2, 0.3};
    map ["Altitude"] = {12000.2, 12001.0 , 12000.5};
    map ["Air Speed"] = {250, 250, 250};
    map ["Heading"] = {45.0, 45.3, 45.8};
    tempMap = map;
    vector<correlatedFeatures> lala;
    string fe1;
    string fe2;
    float tempDeviation = 0;
    float tempPearson = 0;
    const int size = map.begin()->second.size();
    float *first = new float[size];
    float *second = new float[size];
    float *bestFirst = new float[size];
    float *bestSecond = new float[size];
    for (auto &f1: map) {
        fe1 = f1.first;
        tempPearson = 0;
        correlatedFeatures pair;
        pair.feature1 = fe1;
        pair.corrlation = 0;
        tempMap.erase(tempMap.begin());
        for (const auto &f2: tempMap) {
            fe2 = f2.first;
            if (f1 != f2) {
                for (int i = 0; i < size; i++) {
                    first[i] = f1.second[i];
                    second[i] = f2.second[i];
                }
                tempPearson = abs(pearson(first, second, size));
                if (tempPearson > pair.corrlation) {
                    pair.feature2 = fe2;
                    pair.corrlation = tempPearson;
                    cout << pair.corrlation << endl;
                    for (int j = 0; j < size; j++) {
                        bestFirst[j] = f1.second[j];
                        bestSecond[j] = f2.second[j];
                    }
                }
            }
        }
        //now maxPearson contain the best correlative couple for current f1
        if (pair.corrlation > 0.9) {
            cout << "pair:" << pair.feature1 << " and " << pair.feature2;
            cout << " corr:" << pair.corrlation;
            pair.lin_reg = linear_reg(bestFirst, bestSecond, size);
            pair.threshold = 0;
            for (int k = 0; k < size; k++){
                Point p(bestFirst[k], bestSecond[k]);
                tempDeviation = dev(p, pair.lin_reg);
                if (tempDeviation > pair.threshold){
                    pair.threshold = tempDeviation;
                }
            }
            pair.threshold = pair.threshold * 1.1;
            cout << " threshold:" << pair.threshold << endl;
            lala.push_back(pair);
        }
    }
    delete[] first;
    delete[] second;
    delete[] bestFirst;
    delete[] bestSecond;
    //delete[] points;
    cout << "cor num:" << lala.size();

    vector<AnomalyReport> ar;
    for (correlatedFeatures c: lala) {
        cout << "lblbl" << endl;
        string feature1 = c.feature1;
        string feature2 = c.feature2;
        int size = map.begin()->second.size();
        for (int i = 0; i < size; i++) {
            float x = map[feature1][i];
            float y = map[feature2][i];
            cout << "x-" << x << " y-" << y <<endl;
            Point point(x, y);
            cout << "dev:" << dev(point,c.lin_reg) << endl;
            string des = c.feature1 + "-" + c.feature2;
            long step = i + 1;
            cout << "des:" << des << " time:" << step << endl;
            if (dev(point,c.lin_reg) > c.threshold) {

                AnomalyReport a(des, step);
                ar.push_back(a);
            }
        }
    }

}
*/