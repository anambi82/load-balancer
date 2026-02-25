/**
 * @file LoadBalancer.cpp
 * @brief Implementation of the LoadBalancer class.
 */

#include "LoadBalancer.h"
#include <iostream>
#include <random>
#include <cstdlib>

LoadBalancer::LoadBalancer(const Config& config, LogFile* logFile)
    : config(config), logFile(logFile), currTime(0), nextServerId(1), lastScaleTime(0) {
        blockedIpRanges = config.getBlockedIpRanges();
    }

LoadBalancer::~LoadBalancer() {
    for (WebServer* server : servers) {
        delete server;
    }
    servers.clear();
}   

bool LoadBalancer::isIpBlocked(const std::string& ip) const {
    for (const IpRange& range : blockedIpRanges){
        if(range.contains(ip)){
            return true;
        }
    }
    return false;
}

bool LoadBalancer::canScaleUp() const {
    return (currTime - lastScaleTime) >= config.getScaleCooldownTime();
}

void LoadBalancer::addServer() {
    WebServer* newServer = new WebServer(nextServerId++);
    servers.push_back(newServer);
    logFile->logServerAdded(currTime, newServer->getServerId());
    lastScaleTime = currTime;
}

bool LoadBalancer::removeServer() {
    if(servers.size() <= 1){
        return false;
    }
    for(auto i = 0; i < servers.size(); i++){
        if(!servers[i]->isBusy()){
            int serverId = servers[i]->getServerId();
            delete servers[i];
            servers.erase(servers.begin() + i);
            logFile->logServerRemoved(currTime, serverId);
            lastScaleTime = currTime;
            return true;
        }
    }
    return false;
}

void LoadBalancer::checkAndScale() {
    if (!canScaleUp()){
        return;
    }

    int queueSize = requestQueue.size();
    int serverCount = servers.size();
    int minQueue = config.getMinQueuePerServer() * serverCount;
    int maxQueue = config.getMaxQueuePerServer() * serverCount;

    if (queueSize > maxQueue){
        logFile->logEvent(currTime, "SCALE UP: Queue size exceeds max threshold, adding server");
        addServer();
    } else if (queueSize < minQueue && serverCount > 1){
        logFile->logEvent(currTime, "SCALE DOWN: Queue size below min threshold, removing server");
        removeServer();
    }
}

void LoadBalancer::distributeRequests() {
    for (WebServer* server : servers){
        if (!server->isBusy() && !requestQueue.isEmpty()){
            Request req = requestQueue.pop();
            server->assignRequest(req);

            logFile->logRequestStarted(currTime, server->getServerId(), req.getIpIn(), req.getIpOut(), req.getProcessTime());
        }
    }
}

void LoadBalancer::processServers() {
    for (WebServer* server : servers){
        if (server->isBusy()){
            bool completed = server->advanceClockCycle();
            if (completed){
                Request req = server->getCurrentRequest();
                logFile->logRequestProcessed(currTime, server->getServerId(),req.getIpIn(), req.getIpOut(), req.getProcessTime());                
                server->setIdle();
            }
        }
    }
}

void LoadBalancer::addNewRequest() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    if(dis(gen) < config.getNewRequestProb()){
        Request newReq = Request::generateRandomRequest(config.getMinProcessTime(), config.getMaxProcessTime());
        addRequest(newReq);
    }
}

void LoadBalancer::init() {
    logFile->logEvent(currTime, "Initializing Load Balancer");

    int initServers = config.getInitServers();
    for (int i = 0; i < initServers; i++){
        addServer();
    }

    int initQueueSize = initServers * 100;
    for (int i = 0; i < initQueueSize; i++){
        Request newReq = Request::generateRandomRequest(config.getMinProcessTime(), config.getMaxProcessTime());
        addRequest(newReq);
    }

    logFile->logEvent(currTime, "Initialization complete");
    logFile->logStatus(currTime, requestQueue.size(), servers.size());
}

void LoadBalancer::run() {
    int totalRunTime = config.getTotalRunTime();
    int statusInterval = totalRunTime / 20;

    if(statusInterval < 1){
        statusInterval = 1;
    }

    logFile->logEvent(currTime, "RUN: Starting simulation");

    while (currTime < totalRunTime){
        addNewRequest();
        processServers();
        distributeRequests();
        checkAndScale();

        if (currTime % statusInterval == 0){
            logFile->logStatus(currTime, requestQueue.size(), servers.size());
        }

        currTime++;
    }

    logFile->logEvent(currTime, "RUN: Simulation complete");
    
    std::string ipStart = "N/A";
    std::string ipEnd = "N/A";
    
    if (!blockedIpRanges.empty()) {
        ipStart = blockedIpRanges[0].getStartIp();
        ipEnd = blockedIpRanges[0].getEndIp();
    }
    int initServers = config.getInitServers();
    int startingQueueSize = initServers * 100;
    
    logFile->logHeader(
        config.getInitServers(), 
        config.getTotalRunTime(),
        config.getMinProcessTime(),
        config.getMaxProcessTime(),
        startingQueueSize,
        ipStart, 
        ipEnd
    );
    logFile->writeSummary(currTime, servers.size(), requestQueue.size());
}

bool LoadBalancer::addRequest(const Request& request) {
    if(isIpBlocked(request.getIpIn())){
        logFile->logRequestBlocked(currTime, request.getIpIn());
        return false;
    }
    requestQueue.push(request);
    return true;
}

int LoadBalancer::getQueueSize() const {
    return requestQueue.size();
}

int LoadBalancer::getServerCount() const {
    return servers.size();
}

int LoadBalancer::getCurrTime() const {
    return currTime;
}