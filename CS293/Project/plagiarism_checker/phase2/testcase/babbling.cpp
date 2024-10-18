#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <atomic>

std::atomic<int> num_printed(0);
std::mutex m;

void foo(void) {
    while (true) {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "Babble Babble " << num_printed++ << std::endl;
    }
}

void bar(void) {
    while (num_printed < 10) {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "Babble Babble " << num_printed++ << std::endl;
    }
    FILE* fd = fopen("/dev/null", "w");
    std::cout << "Alright! That's enough babbling!" << std::endl;
    dup2(fileno(fd), 1);
}

int main(void) {
    std::thread t1(foo);
    std::thread t2(bar);
    t1.detach();
    t2.join();
    usleep(100000);
    return 0;
}
