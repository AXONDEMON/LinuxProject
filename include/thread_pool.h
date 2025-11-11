#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>
#include <atomic>

class ThreadPool {
public:
    ThreadPool(size_t minThreads = 2, size_t maxThreads = 8);
    ~ThreadPool();

    void enqueue(std::function<void()> task);

private:
    void workerLoop();
    void scaleUp();
    void scaleDown();

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable cv;

    size_t minThreads;
    size_t maxThreads;
    std::atomic<bool> stop;
    std::atomic<bool> resizing;

    // thresholds
    size_t growThreshold = 5;
    size_t shrinkThreshold = 1;
};