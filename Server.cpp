/*
 * Author: Chen Shtar 318731411 & Lidor Ovadia 204268114
 */

#include "Server.h"

string SocketIO::read(){
    string str = "";
    char c = 0;
    recv(clientID, &c, 1,0);
    while (c != '\n') {
        str.append(&c);
        recv(clientID, &c, 1,0);
    }
    return str;
}
void SocketIO::read(float* f){
    string str = read();
    *f = stof(str);
}
void SocketIO::write(string s){
    const char* c = s.c_str();
    send(clientID, c, strlen(c), 0);

}
void SocketIO::write(float f){
    ostringstream strs;
    strs << f;
    string s(strs.str());
    write(s);
}


Server::Server(int port)throw (const char*) {
    flag = false;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        throw "socket failed";
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    if (bind(fd,(struct sockaddr*)&server,sizeof(server)) < 0)
        throw "bind failure";
    if (listen(fd, 3) < 0)
        throw "listen failure";
}

void Server::start(ClientHandler& ch)throw(const char*){
    t = new thread([&ch, this]() {
        while (!flag) {
            socklen_t clientSize = sizeof(client);
            alarm(3);
            int aClient = accept(fd, (struct sockaddr*)&client, &clientSize);
            if (aClient < 0)
                throw "accept failed";
            ch.handle(aClient);
            close(aClient);
            alarm(2);
        }
        close(fd);
    });
}

void Server::stop(){
    flag = true;
    t->join(); // do not delete this!
}

Server::~Server() {
    delete this->t;
}
