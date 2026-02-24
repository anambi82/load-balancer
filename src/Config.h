#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include "IpRange.h"

class Config{
    private:
        int initServers;
        int totalRunTime;
        int minQueuePerServer;
        int maxQueuePerServer;
        int scaleCooldownTime;
        int minProcessTime;
        int maxProcessTime;
        double newRequestProb;
        std::vector<IpRange> blockedIpRanges;
        
        void parseBlockedIpRanges(const std::string& rangesStr);
        void setDefault();
    public:
        Config();

        bool loadFromFile(const std::string& filename);

        int getInitServers() const;
        int getTotalRunTime() const;
        int getMinQueuePerServer() const;
        int getMaxQueuePerServer() const;
        int getScaleCooldownTime() const;
        int getMinProcessTime() const;
        int getMaxProcessTime() const;
        double getNewRequestProb() const;
        const std::vector<IpRange>& getBlockedIpRanges() const;

        void setInitServers(int count);
        void setTotalRunTime(int time);

        void printConfig() const;
};


#endif