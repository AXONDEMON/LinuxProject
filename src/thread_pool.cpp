#include "thread_pool.h"
#include <iostream>

ThreadPool::ThreadPool(size_t minT, size_t maxT)
    : minThreads(minT), maxThreads(maxT), stop(false), resizing(false)
{
    for (size_t i = 0; i < minThreads; i++)
        workers.emplace_back(&ThreadPool::workerLoop, this);
}

ThreadPool::~ThreadPool() {
    stop = true;
    cv.notify_all();

    for (auto &t : workers) {
        if (t.joinable())
            t.join();
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.emplace(task);
    }
    cv.notify_one();
    scaleUp();
}

void ThreadPool::workerLoop() {
    while (!stop) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(queueMutex);

            cv.wait(lock, [&]() {
                return stop || !tasks.empty();
            });

            if (stop && tasks.empty())
                return;

            task = std::move(tasks.front());
            tasks.pop();
        }

        task();
        scaleDown();
    }
}

void ThreadPool::scaleUp() {
    std::unique_lock<std::mutex> lock(queueMutex);
    if (tasks.size() > growThreshold && workers.size() < maxThreads) {
        workers.emplace_back(&ThreadPool::workerLoop, this);
        std::cout << "[+] Scaling UP → Active Threads: " << workers.size() << "\n";
    }
}

void ThreadPool::scaleDown() {
    std::unique_lock<std::mutex> lock(queueMutex);
    if (tasks.size() < shrinkThreshold && workers.size() > minThreads) {
        std::cout << "[-] Scaling DOWN → Active Threads: " << workers.size() - 1 << "\n";
        stop = true;
    }
}