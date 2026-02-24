#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include "Request.h"
#include "RequestQueue.h"
#include "WebServer.h"
#include "IpRange.h"
#include "Config.h"
#include "LogFile.h"

class LoadBalancer{
    private:
        std::vector<WebServer*> servers;
        RequestQueue requestQueue;
        std::vector<IpRange> blockedIpRanges;
        Config config;
        LogFile* logFile;

        int currTime;
        int nextServerId;
        int lastScaleTime;

        bool isIpBlocked(const std::string& ip) const;

        bool canScaleUp() const;

        void checkAndScale();

        void addServer();

        bool removeServer();

        void distributeRequests();

        void processServers();

        void addNewRequest(); // will be based off probability in config
    
    public:
        LoadBalancer(const Config& config, LogFile* logFile);

        ~LoadBalancer();

        void init();

        void run();

        bool addRequest(const Request& request);

        int getQueueSize() const;

        int getServerCount() const;

        int getCurrTime() const;
};


#endif