/**
 * @file LogFile.h
 * @brief Declaration of the LogFile class for simulation event logging.
 */

#ifndef LOGFILE_H
#define LOGFILE_H

#include <string>
#include <fstream>

/// @defgroup TerminalColors ANSI Terminal Color Codes
/// Escape codes used to colorize console output.
/// @{
#define RESET   "\033[0m"   ///< Reset all attributes
#define RED     "\033[31m"  ///< Red text
#define GREEN   "\033[32m"  ///< Green text
#define BLUE    "\033[34m"  ///< Blue text
#define MAGENTA "\033[35m"  ///< Magenta text
#define CYAN    "\033[36m"  ///< Cyan text
#define WHITE   "\033[37m"  ///< White text
#define BOLD    "\033[1m"   ///< Bold text
/// @}

/**
 * @class LogFile
 * @brief Writes simulation events to a log file and optionally to the console.
 *
 * Each log entry is prefixed with a zero-padded clock cycle number. The class
 * also tracks aggregate statistics (servers created/deleted, requests
 * processed/blocked) and writes a formatted summary at the end of the simulation.
 */
class LogFile {
    private:
        std::string filename;      ///< Path to the output log file
        std::ofstream outFile;     ///< Output file stream

        int serversCreated;        ///< Running count of servers added during simulation
        int serversDeleted;        ///< Running count of servers removed during simulation
        int requestsProcessed;     ///< Running count of successfully completed requests
        int requestsBlocked;       ///< Running count of requests rejected due to IP blocking
        bool consoleOutput;        ///< Whether events are also printed to stdout

    public:
        /**
         * @brief Opens the log file and initializes all counters.
         * @param filename Path to the log file to create/overwrite.
         * @param enableConsole If true, events are also echoed to stdout (default: true).
         */
        LogFile(const std::string& filename, bool enableConsole = true);

        /**
         * @brief Destructor. Closes the log file if still open.
         */
        ~LogFile();

        /**
         * @brief Enables or disables mirroring log entries to the console.
         * @param enable true to enable console output, false to suppress it.
         */
        void setConsoleOutput(bool enable);

        /**
         * @brief Writes the simulation starting configuration header to the log file and console.
         * @param initServers Number of servers created at startup.
         * @param runTime Total simulation run time in clock cycles.
         * @param minProcessTime Minimum request processing time in clock cycles.
         * @param maxProcessTime Maximum request processing time in clock cycles.
         * @param startingQueueSize Number of requests pre-loaded into the queue at init.
         * @param ipRangeStart Lower bound of the blocked IP range (or "N/A" if none configured).
         * @param ipRangeEnd Upper bound of the blocked IP range (or "N/A" if none configured).
         */
        void logHeader(int initServers, int runTime, int minProcessTime, int maxProcessTime,
                    int startingQueueSize, const std::string& ipRangeStart, const std::string& ipRangeEnd);

        /**
         * @brief Logs a generic simulation event message.
         * @param cycle Current clock cycle number.
         * @param message Descriptive event message to record.
         */
        void logEvent(int cycle, const std::string& message);

        /**
         * @brief Logs the creation of a new web server.
         * @param cycle Current clock cycle number.
         * @param serverId Unique ID of the server that was added.
         */
        void logServerAdded(int cycle, int serverId);

        /**
         * @brief Logs the removal of an existing web server.
         * @param cycle Current clock cycle number.
         * @param serverId Unique ID of the server that was removed.
         */
        void logServerRemoved(int cycle, int serverId);

        /**
         * @brief Logs the start of request processing by a server.
         * @param cycle Current clock cycle number.
         * @param serverId Unique ID of the server that accepted the request.
         * @param ipIn Source IP address of the request.
         * @param ipOut Destination IP address of the request.
         * @param processTime Number of clock cycles required to process the request.
         */
        void logRequestStarted(int cycle, int serverId, const std::string& ipIn, const std::string& ipOut, int processTime);

        /**
         * @brief Logs the successful completion of a request.
         * @param cycle Current clock cycle number.
         * @param serverId Unique ID of the server that finished the request.
         * @param ipIn Source IP address of the completed request.
         * @param ipOut Destination IP address of the completed request.
         * @param processTime Number of clock cycles the request took to process.
         */
        void logRequestProcessed(int cycle, int serverId, const std::string& ipIn, const std::string& ipOut, int processTime);

        /**
         * @brief Logs a request that was rejected due to a blocked IP range.
         * @param cycle Current clock cycle number.
         * @param ip Source IP address of the blocked request.
         */
        void logRequestBlocked(int cycle, const std::string& ip);

        /**
         * @brief Logs a periodic status snapshot of the simulation state.
         * @param cycle Current clock cycle number.
         * @param queueSize Number of requests currently waiting in the queue.
         * @param serverCount Number of active servers at this cycle.
         */
        void logStatus(int cycle, int queueSize, int serverCount);

        /**
         * @brief Writes a formatted summary of the entire simulation run.
         * @param totalTime Total number of clock cycles the simulation ran.
         * @param finalServerCount Number of servers active at simulation end.
         * @param finalQueueSize Number of requests remaining in the queue at simulation end.
         */
        void writeSummary(int totalTime, int finalServerCount, int finalQueueSize);

        /**
         * @brief Explicitly closes the log file output stream.
         */
        void close();

        /** @brief Returns the total number of servers created during the simulation. */
        int getServersCreated() const;

        /** @brief Returns the total number of servers deleted during the simulation. */
        int getServersDeleted() const;

        /** @brief Returns the total number of requests successfully processed. */
        int getRequestsProcessed() const;

        /** @brief Returns the total number of requests blocked due to IP filtering. */
        int getRequestsBlocked() const;
};

#endif
