#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include <string>

std::vector<std::mutex> locks;
void fun(int n) {
    for (int i = 0; i < 100; i++) {
        locks[n].lock();
        std::cout << "Thread " << n << " is running" << std::endl;
        locks[(n + 1) % locks.size()].unlock();
    }
}

int main(int argc, char** argv) {
    int n = std::stoi(argv[1]);
    locks = std::vector<std::mutex>(n);
    locks[0].unlock();
    for (int i = 1; i < n; i++) {
        locks[i].lock();
    }
    std::vector<std::thread> threads;
    for (int i = 0; i < n; i++) {
        threads.push_back(std::thread(fun, i));
    }
    for (auto &thread : threads) {
        thread.join();
    }
    return 0;
}
