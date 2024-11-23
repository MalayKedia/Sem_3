#include "common.h"

#pragma once
// You should NOT add ANY other includes in this file.
// You also should NOT add `using namespace std;`.

/**
 * FIND THE SERVERS THAT HANDLED THE MOST REQUESTS
 * and also do this task and the task of handling requests efficiently!
 *
 * You are to implement the `servers_t` class and its interface, in the file 
 * `server_requests.cpp`. Define the request id as the number that corresponds
 * to the order in which the request was received, starting from zero. 
 * In other words, after `n` calls to `add_request`, the request id for the 
 * next call should be `n`. The number of servers `k` is passed as an argument 
 * to the constructor of the class, and remains constant throughout.
 *
 * For each request added via `add_request`, say id `i`, you are supposed to do
 * the following:
 * -- If and only if no server is available, then drop the request. Remember
 *          that one server can process at most one request at a time(stamp).
 * -- If server `i % k` is available, then assign the request to server `i % k`.
 *          Here, `k` is the number of servers.
 * -- If server `i % k` is not available, then assign the request to the server
 *          with the smallest id that is just above `i % k` and is available.
 *          If no such server is available, assign the request to the server
 *          with the smallest id that is available.
 * -- If the request is not dropped, that server should be made busy until the
 *          timestamp equal to request duration plus request timestamp, which is
 *          the time taken to complete the request.
 * 
 * All request durations are positive integers, and timestamps nonnegative.
 * Further, the requests are added in strictly increasing order of timestamps.
 * That is, after a request with timestamp `t` is added, all subsequent requests
 * will have timestamps greater than `t`. 
 *
 * It is guaranteed that `k` and `n` both will not exceed 10^5 (one lakh) and 
 * all timestamps and durations will not exceed 10^18 (a huge long integer). 
 * Lastly, the sum of the result set sizes of all calls of 
 * `get_servers_that_served_maximum_requests` will not exceed 10^5 (one lakh).
 *
 * Lastly, you are supposed to implement the method
 * `get_servers_that_served_maximum_requests` that returns the set of servers
 * that served the maximum number of requests. If no requests were served, then
 * return an empty set. Otherwise, it should return a set of size one if only
 * one server served the maximum number of requests, and a set of size greater
 * than one if multiple servers served the same maximum number of requests.
 */

class servers_t {
    // You should NOT modify the public interface of this class.
    // DO NOT implement any method or function in this file.

public:
    servers_t(long long __num_servers);
    ~servers_t(void);
    void add_request(long long __timestamp, long long __duration);
    std::set<long long> get_servers_that_served_maximum_requests(void);
protected:
    // TODO: Add your private members here (ONLY signatures for methods).
    long long next_request_id; // Suggestion -- for request ids.
    // End TODO
};
