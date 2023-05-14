/*
 * Author: Chen Shtar 318731411 & Lidor Ovadia 204268114
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "CLI.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<signal.h>
#include <sstream>


using namespace std;

class ClientHandler{
public:
    virtual void handle(int clientID)=0;
};

class SocketIO:public DefaultIO{
    int clientID;
public:
    SocketIO(int clientID):clientID(clientID){}
    virtual string read();
    virtual void read(float* f);
    virtual void write(string text);
    virtual void write(float f);
    ~SocketIO(){}
};


class AnomalyDetectionHandler:public ClientHandler{
public:
    virtual void handle(int clientID){
        SocketIO sio(clientID);
        CLI cli(&sio);
        cli.start();
    }
};


class Server {
    thread* t; // the thread to run the start() method in
    int fd;
    sockaddr_in server;
    sockaddr_in client;
    bool flag;

public:
    Server(int port) throw (const char*);
    virtual ~Server();
    void start(ClientHandler& ch)throw(const char*);
    void stop();
};

#endif /* SERVER_H_ */
