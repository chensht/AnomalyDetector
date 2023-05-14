/*
 * Author: Chen Shtar 318731411 & Lidor Ovadia 204268114
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO(){}

    void readFile(string fileName){
        ofstream out(fileName);
        string s = read();
        while(s!="done"){
            out<<s<<endl;
            s = read();
        }
        out.close();
    }
};

struct reportAnalysis{
    int start;
    int end;
    string description;
    bool tp;
};

struct info{
    float threshold;
    vector<AnomalyReport> report;
    vector<reportAnalysis> reportsAnalysis;
    int numOfRows;
    info(){
        threshold = 0.9;
        numOfRows = 0;
    }
};

class Command{
protected:
    DefaultIO* dio;
public:
    const string description;
    Command(DefaultIO* dio, const string description):dio(dio), description(description){}
    virtual void execute(info* info)=0;
    virtual ~Command(){}
};

class UploadFiles:public Command{
public:
    UploadFiles(DefaultIO* dio):Command(dio,"1.upload a time series csv file\n"){}
    virtual void execute(info* info){
        dio->write("Please upload your local train CSV file.\n");
        dio->readFile("anomalyTrain.csv");
        dio->write("Upload complete.\nPlease upload your local test CSV file.\n");
        dio->readFile("anomalyTest.csv");
        dio->write("Upload complete.\n");
    }
};

class AlgoSet:public Command{
public:
    AlgoSet(DefaultIO* dio):Command(dio,"2.algorithm settings\n"){}
    virtual void execute(info* info){
        bool valid_threshold = false;
        while(!valid_threshold){
            dio->write("The current correlation threshold is ");
            dio->write(info->threshold);
            dio->write("\nType a new threshold\n");
            float new_threshold;
            dio->read(&new_threshold);
            if(new_threshold > 0 && new_threshold <= 1){
                info->threshold = new_threshold;
                valid_threshold = true;
            }
            else
                dio->write("please choose a value between 0 and 1.\n");
        }
    }
};

class Detect:public Command{
public:
    Detect(DefaultIO* dio):Command(dio,"3.detect anomalies\n"){}
    virtual void execute(info* info){
        TimeSeries train("anomalyTrain.csv");
        TimeSeries test("anomalyTest.csv");
        info->numOfRows = test.getNumOfRows();
        HybridAnomalyDetector ad;
        ad.SetNewThreshold(info->threshold);
        ad.learnNormal(train);
        info->report = ad.detect(test);
        reportAnalysis reportA;
        reportA.start = 0;
        reportA.end = 0;
        reportA.description = "";
        reportA.tp = false;
        for_each(info->report.begin(),info->report.end(),[&reportA,info](AnomalyReport& report){
            if(report.timeStep==reportA.end+1 && report.description==reportA.description)
                reportA.end++;
            else{
                info->reportsAnalysis.push_back(reportA);
                reportA.start=report.timeStep;
                reportA.end=reportA.start;
                reportA.description=report.description;
            }
        });
        info->reportsAnalysis.push_back(reportA);
        info->reportsAnalysis.erase(info->reportsAnalysis.begin());
        dio->write("anomaly detection complete.\n");
    }
};

class Results:public Command{
public:
    Results(DefaultIO* dio):Command(dio,"4.display results\n"){}
    virtual void execute(info* info){
        for_each(info->report.begin(),info->report.end(),[this](AnomalyReport& report){
            dio->write(report.timeStep);
            dio->write("\t "+report.description+"\n");
        });
        dio->write("Done.\n");
    }
};


class AnomaliesAnalysis:public Command{
public:
    AnomaliesAnalysis(DefaultIO* dio):Command(dio,"5.upload anomalies and analyze results\n"){}

    bool crossSection(int aStart,int aEnd,int bStart, int bEnd){
        return (aEnd >= bStart && bEnd >= aStart);
    }
    bool isTP(int start, int end,info* info){
        for(size_t i = 0; i < info->reportsAnalysis.size(); i++){
            reportAnalysis reportA = info->reportsAnalysis[i];
            if(crossSection(start, end, reportA.start, reportA.end)){
                info->reportsAnalysis[i].tp = true;
                return true;
            }
        }
        return false;
    }

    virtual void execute(info* info){
        for(size_t i = 0; i < info->reportsAnalysis.size(); i++){
            info->reportsAnalysis[i].tp = false;
        }
        dio->write("Please upload your local anomalies file.\n");
        string anomaliesFile = dio->read();
        float TP = 0, sum = 0, P = 0;
        while(anomaliesFile != "done"){
            size_t t = 0;
            for(t; anomaliesFile[t] != ','; t++);
            string forStart = anomaliesFile.substr(0, t);
            string forEnd = anomaliesFile.substr(t + 1, anomaliesFile.length());
            int start = stoi(forStart);
            int end = stoi(forEnd);
            if(isTP(start, end, info))
                TP++;
            sum += end + 1- start;
            P++;
            anomaliesFile = dio->read();
        }
        dio->write("Upload complete.\n");
        float FP = 0;
        for(size_t i = 0; i < info->reportsAnalysis.size(); i++)
            if(!info->reportsAnalysis[i].tp)
                FP++;
        float N = info->numOfRows - sum;
        float tpRate = (float(((int)(1000.0*TP/P))/1000.0));
        float fpRate = (float(((int)(1000.0*FP/N))/1000.0));
        dio->write("True Positive Rate: ");
        dio->write(tpRate);
        dio->write("\nFalse Positive Rate: ");
        dio->write(fpRate);
        dio->write("\n");
    }
};

class Exit:public Command{
public:
    Exit(DefaultIO* dio):Command(dio,"6.exit\n"){}
    virtual void execute(info* info){
    }
};



#endif /* COMMANDS_H_ */
