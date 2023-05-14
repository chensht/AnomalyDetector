/*
 * Author: Chen Shtar 318731411 & Lidor Ovadia 204268114
 */

#include "CLI.h"

CLI::CLI(DefaultIO* dio) {
    this->dio=dio;
    commands.push_back(new UploadFiles(dio));
    commands.push_back(new AlgoSet(dio));
    commands.push_back(new Detect(dio));
    commands.push_back(new Results(dio));
    commands.push_back(new AnomaliesAnalysis(dio));
    commands.push_back(new Exit(dio));
}

void CLI::start(){
    info info;
    int clientChoice = 0;
    while(clientChoice != 6){
        dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
        for(size_t i = 0; i < commands.size(); i++){
            dio->write(commands[i]->description);
        }
        string input = dio->read();
        clientChoice = atoi(input.c_str());
        if(clientChoice >= 0 && clientChoice <= 6)
            commands[clientChoice - 1]->execute(&info);
    }
}

CLI::~CLI() {
    for(size_t i = 0; i < commands.size(); i++){
        delete commands[i];
    }
}

