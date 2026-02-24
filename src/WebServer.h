#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

class WebServer {
    private:
        int serverId;
        bool busy;
        Request currRequest;
        int timeRemaining;
    
    public:
        WebServer(int id);

        bool isBusy() const;

        int getServerId() const;

        Request getCurrentRequest() const;

        int getTimeRemaining() const;

        void assignRequest(const Request& request);

        bool advanceClockCycle();

        void setIdle();
};

#endif