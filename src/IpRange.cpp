#include "IpRange.h"
#include <sstream>

IpRange::IpRange(const std::string& startIp, const std::string& endIp)
    : startIp(startIp), endIp(endIp) {
}

long IpRange::ipToNum(const std::string& ip) const {
    long res = 0;
    int part = 0;
    
    std::istringstream iss(ip);
    std::string token;

    while (std::getline(iss, token, '.')){
        part = std::stoi(token);
        res = res * 256 + part;
    }

    return res;
}

bool IpRange::contains(const std::string& ip) const {
    long ipNum = ipToNum(ip);
    return ipNum >= ipToNum(startIp) && ipNum <= ipToNum(endIp);
}

std::string IpRange::getStartIp() const {
    return startIp;
}

std::string IpRange::getEndIp() const {
    return endIp;
}
