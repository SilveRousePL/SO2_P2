//
// Created by darek on 10.04.19.
//

#ifndef SO2_P2_PHILOSOPHER_H
#define SO2_P2_PHILOSOPHER_H

#include <thread>
#include "Fork.h"
#include "Helper.h"
#include "Printer.h"

class Philosopher {
    enum Status{
        THINKING,
        EATING,
        REQUESTING,
        FINISHED
    };

    int id;
    Fork& left_fork;
    Fork& right_fork;
    Status status = Status::THINKING;
    TableChannel& channel;
    std::thread thread;
    Printer& printer;

    int progress = 0;
    int counter = 0;

public:
    Philosopher(int id, Fork &left, Fork &right, TableChannel &table, Printer& printer);
    Philosopher(Philosopher&& obj);
    ~Philosopher();

    void live();

    int getId();
    int getCounter();
    bool isFinished();
    std::string printPhilosopher();
    std::string printStatus();
    std::string printProgress();

private:
    void think();
    void eat();
    void requestForks();
    void freeForks();
    void wait(uint from, uint to);

    void setStatus(Status st);
};

#endif //SO2_P2_PHILOSOPHER_H