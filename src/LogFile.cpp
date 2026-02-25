/**
 * @file LogFile.cpp
 * @brief Implementation of the LogFile class.
 */

#include "LogFile.h"
#include <iostream>
#include <iomanip>

LogFile::LogFile(const std::string& filename, bool enableConsole) 
    : filename(filename), serversCreated(0), serversDeleted(0), 
      requestsProcessed(0), requestsBlocked(0), consoleOutput(enableConsole) {
    
    outFile.open(filename);
    
    if (!outFile.is_open()) {
        std::cerr << RED << "Error: Could not open log file '" << filename << "'" << RESET << std::endl;
    }
}

LogFile::~LogFile() {
    if (outFile.is_open()) {
        outFile.close();
    }
}

void LogFile::setConsoleOutput(bool enable) {
    consoleOutput = enable;
}

void LogFile::logEvent(int cycle, const std::string& message) {
    if (outFile.is_open()) {
        outFile << "[Cycle " << std::setw(5) << std::setfill('0') << cycle << "] " 
                << message << std::endl;
    }

    if (consoleOutput) {
        std::cout << WHITE << "[Cycle " << std::setw(5) << std::setfill('0') << cycle << "] " 
                  << message << RESET << std::endl;
    }
}


void LogFile::logServerAdded(int cycle, int serverId) {
    serversCreated++;
    
    if (outFile.is_open()) {
        outFile << "[Cycle " << std::setw(5) << std::setfill('0') << cycle << "] "
                << "ADDED: Server " << serverId << " created" << std::endl;
    }

    if (consoleOutput) {
        std::cout << GREEN << "[Cycle " << std::setw(5) << std::setfill('0') << cycle << "] "
                  << "ADDED: Server " << serverId << " created" << RESET << std::endl;
    }
}

void LogFile::logServerRemoved(int cycle, int serverId) {
    serversDeleted++;
    
    if (outFile.is_open()) {
        outFile << "[Cycle " << std::setw(5) << std::setfill('0') << cycle << "] "
                << "REMOVED: Server " << serverId << " deallocated" << std::endl;
    }

    if (consoleOutput) {
        std::cout << RED << "[Cycle " << std::setw(5) << std::setfill('0') << cycle << "] "
                  << "REMOVED: Server " << serverId << " deallocated" << RESET << std::endl;
    }
}

void LogFile::logRequestProcessed(int cycle, const std::string& ipIn, const std::string& ipOut) {
    requestsProcessed++;
    
    if (outFile.is_open()) {
        outFile << "[Cycle " << std::setw(5) << std::setfill('0') << cycle << "] "
                << "COMPLETE: Request " << ipIn << " -> " << ipOut << " finished" << std::endl;
    }

    if (consoleOutput) {
        std::cout << CYAN << "[Cycle " << std::setw(5) << std::setfill('0') << cycle << "] "
                  << "COMPLETE: Request " << ipIn << " -> " << ipOut << " finished" << RESET << std::endl;
    }
}

void LogFile::logRequestBlocked(int cycle, const std::string& ip) {
    requestsBlocked++;

    if (outFile.is_open()) {
        outFile << "[Cycle " << std::setw(5) << std::setfill('0') << cycle << "] "
                << "BLOCKED: Request from " << ip << " rejected (IP in blocked range)" << std::endl;
    }

    if (consoleOutput) {
        std::cout << RED << "[Cycle " << std::setw(5) << std::setfill('0') << cycle << "] "
                  << "BLOCKED: Request from " << ip << " rejected (IP in blocked range)" << RESET << std::endl;
    }
}

void LogFile::logStatus(int cycle, int queueSize, int serverCount) {
    if (outFile.is_open()) {
        outFile << "[Cycle " << std::setw(5) << std::setfill('0') << cycle << "] "
                << "STATUS: Queue size: " << queueSize 
                << " | Active servers: " << serverCount << std::endl;
    }

    if (consoleOutput) {
        std::cout << MAGENTA << "[Cycle " << std::setw(5) << std::setfill('0') << cycle << "] "
                  << "STATUS: Queue size: " << queueSize 
                  << " | Active servers: " << serverCount << RESET << std::endl;
    }
}

void LogFile::writeSummary(int totalTime, int finalServerCount, int finalQueueSize) {
    std::string separator = "================================================================================";
    std::string title = "                           SIMULATION SUMMARY";

    if (outFile.is_open()) {
        outFile << std::endl;
        outFile << separator << std::endl;
        outFile << title << std::endl;
        outFile << separator << std::endl;
        outFile << std::endl;
        outFile << "RUN STATISTICS:" << std::endl;
        outFile << "  Total Clock Cycles:          " << totalTime << std::endl;
        outFile << "  Final Server Count:          " << finalServerCount << std::endl;
        outFile << "  Final Queue Size:            " << finalQueueSize << std::endl;
        outFile << std::endl;
        outFile << "REQUEST STATISTICS:" << std::endl;
        outFile << "  Total Requests Processed:    " << requestsProcessed << std::endl;
        outFile << "  Total Requests Blocked:      " << requestsBlocked << std::endl;
        outFile << std::endl;
        outFile << "SERVER STATISTICS:" << std::endl;
        outFile << "  Servers Created:             " << serversCreated << std::endl;
        outFile << "  Servers Deleted:             " << serversDeleted << std::endl;
        outFile << std::endl;
        outFile << separator << std::endl;
    }

    if (consoleOutput) {
        std::cout << std::endl;
        std::cout << BOLD << BLUE << separator << RESET << std::endl;
        std::cout << BOLD << BLUE << title << RESET << std::endl;
        std::cout << BOLD << BLUE << separator << RESET << std::endl;
        std::cout << std::endl;
        std::cout << BOLD << WHITE << "RUN STATISTICS:" << RESET << std::endl;
        std::cout << "  Total Clock Cycles:          " << totalTime << std::endl;
        std::cout << "  Final Server Count:          " << finalServerCount << std::endl;
        std::cout << "  Final Queue Size:            " << finalQueueSize << std::endl;
        std::cout << std::endl;
        std::cout << BOLD << WHITE << "REQUEST STATISTICS:" << RESET << std::endl;
        std::cout << "  Total Requests Processed:    " << GREEN << requestsProcessed << RESET << std::endl;
        std::cout << "  Total Requests Blocked:      " << RED << requestsBlocked << RESET << std::endl;
        std::cout << std::endl;
        std::cout << BOLD << WHITE << "SERVER STATISTICS:" << RESET << std::endl;
        std::cout << "  Servers Created:             " << GREEN << serversCreated << RESET << std::endl;
        std::cout << "  Servers Deleted:             " << RED << serversDeleted << RESET << std::endl;
        std::cout << std::endl;
        std::cout << BOLD << BLUE << separator << RESET << std::endl;
    }
}

void LogFile::close() {
    if (outFile.is_open()) {
        outFile.close();
    }
}

int LogFile::getServersCreated() const {
    return serversCreated;
}

int LogFile::getServersDeleted() const {
    return serversDeleted;
}

int LogFile::getRequestsProcessed() const {
    return requestsProcessed;
}

int LogFile::getRequestsBlocked() const {
    return requestsBlocked;
}