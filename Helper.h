//
// Created by darek on 10.04.19.
//

#ifndef SO2_P2_HELPER_H
#define SO2_P2_HELPER_H

#include <iostream>
#include <mutex>
#include <condition_variable>

class Coordinator {
    std::mutex mutex;
    std::condition_variable cv;

public:
    void wait() {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock);
    }

    void notifyAll() {
        std::unique_lock<std::mutex> lock(mutex);
        cv.notify_all();
    }
};

class TableChannel {
public:
    Coordinator coordinator;
    bool dinner_finished = false;
};

class ThreadSafePrinter {
    static std::mutex cout_mutex;

public:
    static void print(std::string const &text) {
        std::lock_guard<std::mutex> lock_guard(cout_mutex);
        std::cout << text << std::endl;
    }
};

#endif //SO2_P2_HELPER_H