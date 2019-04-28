//
// Created by darek on 10.04.19.
//

#ifndef SO2_P2_FORK_H
#define SO2_P2_FORK_H

#include <mutex>

class Fork {
    enum Status {
        DIRTY,
        CLEAN,
    };

    int id;
    int owner_id;

    std::mutex mutex;

    Status status = DIRTY;

public:
    Fork(int fork_id, int owner_id)
        : id(fork_id), owner_id(owner_id) {}
    Fork(const Fork& obj)
        : id(obj.id), owner_id(obj.owner_id) {}

    void request(int philosopher_id) {
        while (owner_id != philosopher_id) {
            if (isDirty()) {
                std::lock_guard<std::mutex> lock(mutex);
                wash();
                owner_id = philosopher_id;
            }
        }
    }

    void free() {
        dirty();
    }

    std::mutex& getMutex() {
        return mutex;
    }

    int getId() {
        return id;
    }

    int getOwnerId() {
        return owner_id;
    }

    std::string printStatus() {
        return "F:" + std::to_string(id) + " <= " + "P:" + std::to_string(owner_id) + " | " + (isDirty() ? std::string("Dirty") : std::string("Clean"));
    }

    bool isDirty() {
        return status == DIRTY ? true : false;
    }

    bool isClean() {
        return status == CLEAN ? true : false;
    }

private:
    void dirty() {
        status = DIRTY;
    }

    void wash() {
        status = CLEAN;
    }
};

#endif //SO2_P2_FORK_H