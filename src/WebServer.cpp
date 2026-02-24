#include "WebServer.h"

WebServer::WebServer(int id) : serverId(id), busy(false), timeRemaining(0) {
}

bool WebServer::isBusy() const{
    return busy;
}

int WebServer::getServerId() const{
    return serverId;
}

Request WebServer::getCurrentRequest() const{
    return currRequest;
}

int WebServer::getTimeRemaining() const{
    return timeRemaining;
}

void WebServer::assignRequest(const Request& request){
    currRequest = request;
    timeRemaining = request.getProcessTime();
    busy = true;
}

bool WebServer::advanceClockCycle(){
    if (!busy) {
        return false;
    }

    timeRemaining--;

    if (timeRemaining <= 0) {
        busy = false;
        return true; // request completed
    }

    return false; // request still processing
}

void WebServer::setIdle(){
    busy = false;
    timeRemaining = 0;
}