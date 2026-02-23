#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <queue>
#include "Request.h"

class RequestQueue {
    private:
        std::queue<Request> queue;
    public:
        RequestQueue();
        void push(const Request& request);
        Request pop();
        bool isEmpty() const;
        int size() const;
        Request front() const;
};

#endif