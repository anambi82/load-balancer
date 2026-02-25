/**
 * @file RequestQueue.cpp
 * @brief Implementation of the RequestQueue class.
 */

#include "RequestQueue.h"

RequestQueue::RequestQueue() {

}

void RequestQueue::push(const Request& request){
    queue.push(request);
}

Request RequestQueue::pop(){
    if (queue.empty()) {
        throw std::runtime_error("Queue is empty");
    }
    Request frontRequest = queue.front();
    queue.pop();
    return frontRequest;
}

bool RequestQueue::isEmpty() const {
    return queue.empty();
}

int RequestQueue::size() const {
    return queue.size();
}

Request RequestQueue::front() const {
    if (queue.empty()) {
        throw std::runtime_error("Queue is empty");
    }
    return queue.front();
}
