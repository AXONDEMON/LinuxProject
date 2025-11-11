#include "../include/thread_pool.h"
#include <iostream>
#include <chrono>

void exampleTask(int id) {
    std::cout << "Task " << id << " executed\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

int main() {
    ThreadPool pool(2, 6);

    for(int i = 1; i <= 20; i++){
        pool.enqueue([i](){ exampleTask(i); });
    }

    // wait before shutdown
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}