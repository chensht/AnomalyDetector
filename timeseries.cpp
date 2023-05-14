/*
 * Author: Chen Shtar 318731411 & Lidor Ovadia 204268114
 */

#include "timeseries.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


// this function separate a string into a vector of strings by commas and return the vector
vector<string> TimeSeries::separateLine(string line){
    vector<string> separatedData;
    // str - the temp value which turn into a string in the vector
    string str;
    // as long as the line isn't the last part that separate by commas
    while (line != str){
        // init the str to be the first part (till first comma)
        str = line.substr(0, line.find(','));
        // put the first temp string into the vector of strings
        separatedData.push_back(str);
        // erase the first part that separated by commas from 'line' string
        line = line.substr(line.find(',') + 1, line.length());
    }
    return separatedData;
}

// this function add the values accordingly to each feature in the map
void TimeSeries::addValues(map<string, vector<float>> &data, vector<string> features, vector<string> values){
    for (int i = 0; i < values.size(); i++) {
        // adding the value (converting to float) to the key (feature) in addition to what it already contains
        data[features[i]].push_back(stof(values[i]));
    }
}

// this function read an CSV file and put the data into a map with the help of previously functions
void TimeSeries::readCSVFile(const char* CSVFileName) {
    // opening the file
    ifstream CSVFile(CSVFileName);
    if (!CSVFile.is_open()) {
        throw runtime_error("Could not open file");
    }
    // line will contain one line that have been read from the file
    string line;
    getline(CSVFile, line);
    // saving the first line which is the features line
    this->features = separateLine(line);
    // tempValues will contain temporarily the next line from the file
    vector<string> tempValues;
    // as long as there are more lines tor read
    while (getline(CSVFile, line)) {
        // separated the line (string) into vector of strings
        tempValues = separateLine(line);
        // adding the values according to the features
        addValues(this->dataSet, this->features, tempValues);
    }
    CSVFile.close();
}

map<string, vector<float>> TimeSeries:: getDataSet() const {
    return this->dataSet;
}

vector<string> TimeSeries::getFeatures () const {
    return this->features;
}

vector<float> TimeSeries::getValues(string feature) const {
    return this->getDataSet()[feature];
}

int TimeSeries::getNumOfRows() const {
    return this->features.size();
}


