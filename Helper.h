//
// Created by darek on 10.04.19.
//

#ifndef SO2_P2_HELPER_H
#define SO2_P2_HELPER_H

#include <mutex>
#include <condition_variable>

class Sync {
    std::mutex mutex;
    std::condition_variable cv;

public:
    void wait() {
        std::unique_lock <std::mutex> lock(mutex);
        cv.wait(lock);
    }

    void notifyAll() {
        std::unique_lock <std::mutex> lock(mutex);
        cv.notify_all();
    }
};

class TableChannel {
public:
    Sync sync;
    bool dinner_finished = false;
};

#endif //SO2_P2_HELPER_H