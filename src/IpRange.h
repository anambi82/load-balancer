#ifndef IPRANGE_H
#define IPRANGE_H

#include <string>

class IpRange{
    private:
        std::string startIp;
        std::string endIp;
        long ipToNum(const std::string& ip) const;
    public:
        IpRange(const std::string& startIp, const std::string& endIp);

        bool contains(const std::string& ip) const;

        std::string getStartIp() const;

        std::string getEndIp() const;
};

#endif