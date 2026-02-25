/**
 * @file Config.cpp
 * @brief Implementation of the Config class.
 */

#include "Config.h"
#include <fstream>
#include <sstream>
#include <iostream>

Config::Config() {
    setDefault();
}

void Config::setDefault() {
    initServers = 10;
    totalRunTime = 10000;
    minQueuePerServer = 50;
    maxQueuePerServer = 80;
    scaleCooldownTime = 100;
    minProcessTime = 5;
    maxProcessTime = 20;
    newRequestProb = 0.25;
    blockedIpRanges.clear();
}

void Config::parseBlockedIpRanges(const std::string& rangesStr){
    blockedIpRanges.clear();

    if (rangesStr.empty()) {
        return;
    }

    std::istringstream iss(rangesStr);
    std::string range;

    while (std::getline(iss, range, ',')){
        size_t dash_pos = range.find('-');

        if (dash_pos != std::string::npos) {
            std::string startIp = range.substr(0, dash_pos);
            std::string endIp = range.substr(dash_pos + 1);

            blockedIpRanges.push_back(IpRange(startIp, endIp));
        }
    }
}

bool Config::loadFromFile(const std::string& filename){
    std::ifstream file(filename);

    if (!file.is_open()){
        std::cerr << "Failed to open config file: " << filename << std::endl;
        return false;
    }

    std::string line;

    while(std::getline(file, line)){
        if (line.empty() || line[0] == '#') {
            continue; //skip comments and empty liens
        } 
        size_t equal_pos = line.find('=');

        if(equal_pos == std::string::npos){
            continue;
        }

        std::string key = line.substr(0, equal_pos);
        std::string value = line.substr(equal_pos + 1);

        if (key == "initServers") {
            initServers = std::stoi(value);
        } else if (key == "totalRunTime") {
            totalRunTime = std::stoi(value);
        } else if (key == "minQueuePerServer") {
            minQueuePerServer = std::stoi(value);
        } else if (key == "maxQueuePerServer") {
            maxQueuePerServer = std::stoi(value);
        } else if (key == "scaleCooldownTime") {
            scaleCooldownTime = std::stoi(value);
        } else if (key == "minProcessTime") {
            minProcessTime = std::stoi(value);
        } else if (key == "maxProcessTime") {
            maxProcessTime = std::stoi(value);
        } else if (key == "newRequestProb") {
            newRequestProb = std::stod(value);
        } else if (key == "blockedIpRanges") {
            parseBlockedIpRanges(value);
        }
    }
    file.close();
    return true;
}

int Config::getInitServers() const {
    return initServers;
}

int Config::getTotalRunTime() const {
    return totalRunTime;
}

int Config::getMinQueuePerServer() const {
    return minQueuePerServer;
}

int Config::getMaxQueuePerServer() const {
    return maxQueuePerServer;
}

int Config::getScaleCooldownTime() const {
    return scaleCooldownTime;
}

int Config::getMinProcessTime() const {
    return minProcessTime;
}

int Config::getMaxProcessTime() const {
    return maxProcessTime;
}

double Config::getNewRequestProb() const {
    return newRequestProb;
}

const std::vector<IpRange>& Config::getBlockedIpRanges() const {
    return blockedIpRanges;
}

void Config::setInitServers(int count) {
    initServers = count;
}

void Config::setTotalRunTime(int time) {
    totalRunTime = time;
}

void Config::printConfig() const {
    std::cout << "===== Current Configuration =====" << std::endl;
    std::cout << "initServers:                     " << initServers << std::endl;
    std::cout << "totalRunTime:                    " << totalRunTime << std::endl;
    std::cout << "minQueuePerServer:               " << minQueuePerServer << std::endl;
    std::cout << "maxQueuePerServer:               " << maxQueuePerServer << std::endl;
    std::cout << "scaleCooldownTime:               " << scaleCooldownTime << std::endl;
    std::cout << "minProcessTime:                  " << minProcessTime << std::endl;
    std::cout << "maxProcessTime:                  " << maxProcessTime << std::endl;
    std::cout << "newRequestProb:                  " << newRequestProb << std::endl;

    std::cout << "blockedIpRanges: ";
    for (const auto& range : blockedIpRanges) {
        std::cout << range.getStartIp() << "-" << range.getEndIp() << ", ";
    }
    std::cout << std::endl;
    std::cout << "================================="<< std::endl;
}