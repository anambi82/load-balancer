/**
 * @file LoadBalancer.h
 * @brief Declaration of the LoadBalancer class, the central simulation controller.
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include "Request.h"
#include "RequestQueue.h"
#include "WebServer.h"
#include "IpRange.h"
#include "Config.h"
#include "LogFile.h"

/**
 * @class LoadBalancer
 * @brief Orchestrates the simulation of a dynamically scaling server pool.
 *
 * On each clock cycle the LoadBalancer:
 *  1. Probabilistically generates a new incoming request.
 *  2. Advances all busy servers by one clock cycle, completing requests where due.
 *  3. Distributes queued requests to idle servers (round-robin over available slots).
 *  4. Evaluates scaling thresholds and adds or removes servers as needed.
 *
 * Requests originating from blocked IP ranges are silently dropped and logged.
 * Autoscaling is gated by a configurable cooldown period to prevent thrashing.
 */
class LoadBalancer{
    private:
        std::vector<WebServer*> servers;    ///< Pool of dynamically managed server instances
        RequestQueue requestQueue;          ///< FIFO queue of pending requests
        std::vector<IpRange> blockedIpRanges; ///< IP ranges that are filtered at ingress
        Config config;                      ///< Simulation configuration parameters
        LogFile* logFile;                   ///< Pointer to the shared log file (non-owning)

        int currTime;        ///< Current simulation clock cycle
        int nextServerId;    ///< ID to assign to the next server created
        int lastScaleTime;   ///< Clock cycle at which the last scaling event occurred

        /**
         * @brief Checks whether the given IP is covered by any blocked range.
         * @param ip IPv4 address string to test.
         * @return true if the IP is blocked, false otherwise.
         */
        bool isIpBlocked(const std::string& ip) const;

        /**
         * @brief Checks whether enough time has elapsed since the last scaling event.
         * @return true if scaling is permitted at the current cycle, false if still in cooldown.
         */
        bool canScaleUp() const;

        /**
         * @brief Evaluates queue depth against thresholds and triggers scale-up or scale-down.
         *
         * Does nothing if the cooldown period has not elapsed since the last scaling event.
         */
        void checkAndScale();

        /**
         * @brief Allocates a new WebServer, adds it to the pool, and logs the event.
         */
        void addServer();

        /**
         * @brief Removes the first idle server from the pool and logs the event.
         * @return true if a server was successfully removed, false if none are idle or only one server remains.
         */
        bool removeServer();

        /**
         * @brief Assigns queued requests to idle servers.
         *
         * Iterates over the server pool and dequeues one request per idle server.
         */
        void distributeRequests();

        /**
         * @brief Advances all busy servers by one clock cycle and logs completed requests.
         */
        void processServers();

        /**
         * @brief Randomly generates and enqueues a new request based on the configured probability.
         */
        void addNewRequest();

    public:
        /**
         * @brief Constructs a LoadBalancer with the given configuration and log file.
         * @param config Simulation configuration parameters.
         * @param logFile Pointer to an open LogFile for event recording (must outlive this object).
         */
        LoadBalancer(const Config& config, LogFile* logFile);

        /**
         * @brief Destructor. Frees all dynamically allocated WebServer objects.
         */
        ~LoadBalancer();

        /**
         * @brief Creates the initial server pool and seeds the request queue.
         *
         * Spins up initServers servers and pre-fills the queue with
         * initServers * 100 randomly generated requests before the main loop begins.
         */
        void init();

        /**
         * @brief Runs the main simulation loop for the configured number of clock cycles.
         *
         * Each cycle: generates requests, processes servers, distributes work, and checks scaling.
         * Logs a status snapshot every totalRunTime/20 cycles.
         */
        void run();

        /**
         * @brief Submits a request to the queue, blocking it if the source IP is filtered.
         * @param request The Request to add.
         * @return true if the request was enqueued, false if it was blocked.
         */
        bool addRequest(const Request& request);

        /**
         * @brief Returns the current number of requests waiting in the queue.
         * @return Queue size.
         */
        int getQueueSize() const;

        /**
         * @brief Returns the number of servers currently in the pool.
         * @return Server count.
         */
        int getServerCount() const;

        /**
         * @brief Returns the current simulation clock cycle.
         * @return Current time.
         */
        int getCurrTime() const;
};


#endif
