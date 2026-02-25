/**
 * @file WebServer.h
 * @brief Declaration of the WebServer class representing a single server in the pool.
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

/**
 * @class WebServer
 * @brief Models a single server that processes one Request at a time.
 *
 * Each WebServer has a unique ID and tracks whether it is currently busy,
 * the request it is processing, and how many clock cycles remain before
 * the current request completes.
 */
class WebServer {
    private:
        int serverId;          ///< Unique identifier assigned by the LoadBalancer
        bool busy;             ///< True if the server is currently processing a request
        Request currRequest;   ///< The request currently being processed
        int timeRemaining;     ///< Clock cycles remaining to finish the current request

    public:
        /**
         * @brief Constructs a WebServer with the given ID in an idle state.
         * @param id Unique server identifier.
         */
        WebServer(int id);

        /**
         * @brief Checks whether the server is currently processing a request.
         * @return true if busy, false if idle.
         */
        bool isBusy() const;

        /**
         * @brief Returns the unique identifier for this server.
         * @return Server ID.
         */
        int getServerId() const;

        /**
         * @brief Returns a copy of the request currently being processed.
         * @return Current Request object.
         */
        Request getCurrentRequest() const;

        /**
         * @brief Returns the number of clock cycles remaining for the current request.
         * @return Remaining processing time in clock cycles.
         */
        int getTimeRemaining() const;

        /**
         * @brief Assigns a request to this server and marks it as busy.
         * @param request The Request to process.
         */
        void assignRequest(const Request& request);

        /**
         * @brief Advances the server by one clock cycle.
         *
         * Decrements the remaining processing time. If it reaches zero, the
         * server becomes idle and the request is considered complete.
         *
         * @return true if the current request just completed, false otherwise.
         */
        bool advanceClockCycle();

        /**
         * @brief Forcefully sets the server to idle, clearing any remaining work.
         */
        void setIdle();
};

#endif
