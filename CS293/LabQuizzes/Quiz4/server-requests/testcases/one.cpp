#include "server_requests.h"
// You should NOT modify ANYTHING in this file.

bool __evaluate_testcase_one(void) {
    class servers_t servers(3);
    servers.add_request(1, 5);
    servers.add_request(2, 2);
    servers.add_request(3, 3);
    servers.add_request(4, 3);
    servers.add_request(5, 3);
    std::set<long long> result;
    result = servers.get_servers_that_served_maximum_requests();
    std::set<long long> correct_result = {1};
    if (result != correct_result) {
        return false;
    }
    return true;
}
