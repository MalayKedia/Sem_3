#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <thread>
#include <mutex>
#include <random>
#include <queue>

struct data_t {
    void enqueue(std::array<int, 10> __data) {
        std::lock_guard<std::mutex> lock(this->lock);
        this->data.push(__data);
    }
    std::array<int, 10> dequeue(void) {
        std::lock_guard<std::mutex> lock(this->lock);
        std::array<int, 10> __data = this->data.front();
        this->data.pop();
        return __data;
    }
protected:
    std::mutex lock;
    std::queue<std::array<int, 10>> data;
};

struct sender_t {
    sender_t(std::shared_ptr<data_t> __data) : data(__data) {
        this->main_fn = std::thread([this](void) {
            while (true) {
                std::lock_guard<std::mutex> lock(this->lock);
                if (this->data.empty()) continue;
                std::array<int, 10> __data = this->data.front();
                this->data.pop();
                bool is_zero_arr = true;
                for (int i = 0; i < 10; i++) {
                    if (__data[i] != 0) {
                        is_zero_arr = false;
                        break;
                    }
                }
                if (is_zero_arr) {
                    std::cout << "Zero array detected!" << std::endl;
                    break;
                } else {
                    this->shared_data->enqueue(__data);
                }       
            }
        });
    }
    ~sender_t() {
        this->main_fn.join();
    }
    void send(std::array<int, 10> __data) {
        std::lock_guard<std::mutex> lock(this->lock);
        this->data.push(__data);
    }
protected:
    std::thread main_fn;
    std::shared_ptr<data_t> shared_data;
    std::mutex lock;
    std::queue<std::array<int, 10>> data;
};

struct receiver_t {
    receiver_t(std::shared_ptr<data_t> __data) : data(__data) {
        this->is_running = true;
        this->main_fn = std::thread([this](void) {
            while (is_running) {
                std::array<int, 10> __data = this->shared_data->dequeue();
                bool is_zero_arr = true;
                for (int i = 0; i < 10; i++) {
                    if (__data[i] != 0) {
                        is_zero_arr = false;
                        break;
                    }
                }
                if (is_zero_arr) {
                    std::cout << "Zero array detected!" << std::endl;
                    break;
                } else {
                    std::lock_guard<std::mutex> lock(this->lock);
                    this->data->enqueue(data);
                }
            }
        });
    }
    ~receiver_t() {
        this->is_running = false;
        this->main_fn.join();
    }
    std::array<int, 10> receive(void) {
        std::lock_guard<std::mutex> lock(this->lock);
        std::array<int, 10> __data = this->data.front();
        this->data.pop();
        return __data;
    }
protected:
    std::thread main_fn;
    std::shared_ptr<data_t> shared_data;
    std::mutex lock;
    std::queue<std::array<int, 10>> data;
    std::atomic<bool> is_running;
};

void send_random_datas_to(std::mt19937 gen, sender_t &sender, int num_data) {
    for (int i = 0; i < num_data; i++) {
        std::array<int, 10> __data;
        for (int j = 0; j < 10; j++) {
            __data[j] = -100 + gen() % 200;
        }
        usleep(gen() % 100000);
        sender.send(__data);
    }
    usleep(gen() % 100000);
    std::array<int, 10> zero_arr;
    zero_arr.fill(0);
    sender.send(zero_arr);
}

int main(void) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shared_ptr<data_t> data = std::make_shared<data_t>();
    sender_t sender(data);
    receiver_t receiver(data);
    std::thread sender_thread(send_random_datas_to, gen, std::ref(sender), 10);
    sender_thread.join();
    usleep(1000000);
    for (int i = 0; i < 10; i++) {
        std::array<int, 10> __data = receiver.receive();
        for (int j = 0; j < 10; j++) {
            std::cout << __data[j] << " ";
        }
        std::cout << std::endl;
    }
    receiver.receive();
    return 0;
}
