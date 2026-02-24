#ifndef LOGFILE_H
#define LOGFILE_H

#include <string>
#include <fstream>

// terimnal color codes for console output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"


class LogFile {
    private:
        std::string filename;
        std::ofstream outFile;

        int serversCreated;
        int serversDeleted;
        int requestsProcessed;
        int requestsBlocked;
        bool consoleOutput;

    public:
        LogFile(const std::string& filename, bool enableConsole = true);
    
        ~LogFile();

        void setConsoleOutput(bool enable);
    
        void logEvent(int cycle, const std::string& message);

        void logServerAdded(int cycle, int serverId);
    
        void logServerRemoved(int cycle, int serverId);

        void logRequestProcessed(int cycle, const std::string& ipIn, const std::string& ipOut);

        void logRequestBlocked(int cycle, const std::string& ip);
        
        void logStatus(int cycle, int queueSize, int serverCount);

        void writeSummary(int totalTime, int finalServerCount, int finalQueueSize);
    
        void close();

        int getServersCreated() const;
        int getServersDeleted() const;
        int getRequestsProcessed() const;
        int getRequestsBlocked() const;
    };

#endif