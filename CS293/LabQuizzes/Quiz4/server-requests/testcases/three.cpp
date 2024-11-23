#include "server_requests.h"
// You should NOT modify ANYTHING in this file.

bool __evaluate_testcase_three(void) {
    class servers_t servers(10000);
    for (long long i = 0; i < 10000; i++) {
        servers.add_request(i * 1000, 1'000'000'000'000 - i * 10000);
    }
    std::set<long long> result;
    result = servers.get_servers_that_served_maximum_requests();
    std::set<long long> correct_result;
    for (long long i = 0; i < 10000; i++) {
        correct_result.insert(i);
    }
    if (result != correct_result) {
        return false;
    }
    for (long long i = 0; i < 5000; i++) {
        servers.add_request(i * 1000 + 1'000'000'000,
                1'000'000'000'000 - i * 1000); // all dropped
    }
    servers.add_request(1'000'000'000'000 - 9000 * 7000, 1'000'000'000'000);
    result = servers.get_servers_that_served_maximum_requests();
    correct_result.clear();
    correct_result.insert(7000);
    if (result != correct_result) {
        return false;
    }
    return true;
}
