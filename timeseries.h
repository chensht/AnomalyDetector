/*
 * Author: Chen Shtar 318731411 & Lidor Ovadia 204268114
 */

#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <string>
#include <vector>
#include <map>
using namespace std;

class TimeSeries{
public:
    TimeSeries (const char* CSVfileName){
        readCSVFile(CSVfileName);
    }
    // the map who will contain the data from CSV file
    map<string, vector<float>> dataSet;
    // the features from the file
    vector<string> features;
    // this function will separate a string into a vector of strings by commas
    vector<string> separateLine (string line);
    // this function will add the values accordingly to each key (feature) in the map
    void addValues (map<string, vector<float>>& data, vector<string> keys, vector<string> values);
    // this function will read the CSV file and put the data into a map with the help of previously functions
    void readCSVFile (const char* CSVFileName);
    map<string, vector<float>> getDataSet() const;
    vector<string> getFeatures () const;
    vector<float> getValues (string key) const;
    int getNumOfRows () const;





};


#endif /* TIMESERIES_H_ */
