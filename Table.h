//
// Created by darek on 10.04.19.
//

#ifndef SO2_P2_TABLE_H
#define SO2_P2_TABLE_H

#include <deque>
#include "Philosopher.h"
#include "Printer.h"

class Table {
    std::deque <Fork> fork;
    std::deque <Philosopher> philosopher;
    size_t number;
    TableChannel channel;
    Printer printer;

public:

    Table(size_t number) : number(number), printer(channel) {
        for (uint i{0}; i < number; ++i) {
            fork.emplace_back(i, i % (number - 1));
        }
        for (uint i{0}; i < number; ++i) {
            philosopher.emplace_back(i, fork[i], fork[(i + 1) % number], channel, printer);
        }

        std::vector <std::string> id_str, status_str, progress_str;
        std::vector<bool> is_finished;
        for (auto &item : philosopher) {
            id_str.emplace_back(item.printPhilosopher());
            status_str.emplace_back(item.printStatus());
            progress_str.emplace_back(item.printProgress());
            is_finished.emplace_back(item.isFinished());
        }
        printer.initTableInfo(id_str, status_str, progress_str, is_finished);
    }

    void start() {
        channel.sync.notifyAll();
        printer.start();
    }
};

#endif //SO2_P2_TABLE_H