#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request{
    private:
        std::string ipIn;
        std::string ipOut;
        int processTime;
        char jobType;
    public:
        Request();

        Request(std::string ipIn, std::string ipOut, int processTime, char jobType);

        std::string getIpIn() const;
        std::string getIpOut() const;
        int getProcessTime() const;
        char getJobType() const;

        static std::string generateRandomIp();

        static Request generateRandomRequest(int minTime, int maxTime);
};

#endif
