/**
 * @file RequestQueue.h
 * @brief Declaration of the RequestQueue class, a FIFO queue for network requests.
 */

#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <queue>
#include "Request.h"

/**
 * @class RequestQueue
 * @brief A FIFO queue that buffers incoming Request objects awaiting server assignment.
 *
 * Wraps std::queue<Request> with bounds-checked access and convenience methods
 * used by the LoadBalancer to manage pending requests.
 */
class RequestQueue {
    private:
        std::queue<Request> queue;  ///< Underlying standard queue of Request objects
    public:
        /**
         * @brief Default constructor. Creates an empty request queue.
         */
        RequestQueue();

        /**
         * @brief Adds a request to the back of the queue.
         * @param request The Request to enqueue.
         */
        void push(const Request& request);

        /**
         * @brief Removes and returns the request at the front of the queue.
         * @return The oldest Request in the queue.
         * @throws std::runtime_error if the queue is empty.
         */
        Request pop();

        /**
         * @brief Checks whether the queue contains no requests.
         * @return true if the queue is empty, false otherwise.
         */
        bool isEmpty() const;

        /**
         * @brief Returns the number of requests currently in the queue.
         * @return Current queue size.
         */
        int size() const;

        /**
         * @brief Returns the request at the front of the queue without removing it.
         * @return A copy of the front Request.
         * @throws std::runtime_error if the queue is empty.
         */
        Request front() const;
};

#endif
