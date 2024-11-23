#include "server_requests.h"
// You should NOT modify ANYTHING in this file.

bool __evaluate_testcase_two(void) {
    class servers_t servers(5);
    std::set<long long> result;
    result = servers.get_servers_that_served_maximum_requests();
    std::set<long long> correct_result = {};
    if (result != correct_result) {
        return false;
    }
    servers.add_request(0, 500000);
    servers.add_request(200000, 1000000);
    servers.add_request(300000, 1000000);
    servers.add_request(300100, 600000);
    servers.add_request(300200, 500000);
    servers.add_request(300300, 500000); // dropped
    servers.add_request(300400, 500000); // dropped
    servers.add_request(500500, 500000);
    servers.add_request(801000, 500000);
    result = servers.get_servers_that_served_maximum_requests();
    correct_result = {0, 4};
    if (result != correct_result) {
        return false;
    }
    return true;
}
