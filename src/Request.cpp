#include "Request.h"
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <random>

Request::Request() : ipIn("000.000.000"), ipOut("000.000.000"), processTime(0), jobType('P') {
}

Request::Request(std::string ipIn, std::string ipOut, int processTime, char jobType)
    : ipIn(ipIn), ipOut(ipOut), processTime(processTime), jobType(jobType){
}

std::string Request::getIpIn() const {
    return ipIn;
}

std::string Request::getIpOut() const {
    return ipOut;
}

int Request::getProcessTime() const {
    return processTime;
}

char Request::getJobType() const {
    return jobType;
}

std::string Request::generateRandomIp() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    std::ostringstream oss;
    oss << std::setw(3) << std::setfill('0') << dis(gen) << "."
        << std::setw(3) << std::setfill('0') << dis(gen) << "."
        << std::setw(3) << std::setfill('0') << dis(gen);

    return oss.str();
}

Request Request::generateRandomRequest(int minTime, int maxTime){
    std::string ipIn = generateRandomIp();
    std::string ipOut = generateRandomIp();

    int processTime = minTime + (rand() % (maxTime - minTime + 1));
    char jobType = (rand() % 2 == 0) ? 'P' : 'S';

    return Request(ipIn, ipOut, processTime, jobType);
}