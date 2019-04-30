//
// Created by darek on 10.04.19.
//

#ifndef SO2_P2_PRINTER_H
#define SO2_P2_PRINTER_H

#include <ncurses.h>
#include <vector>
#include <thread>
#include "Helper.h"

class Printer {
    std::vector <std::string> philosopher_id;
    std::vector <std::string> philosopher_status;
    std::vector <std::string> philosopher_progress;
    std::vector<bool> philosopher_finished;

    std::string status;

    TableChannel &channel;

public:
    Printer(TableChannel &channel);

    ~Printer();

    void start();

    void initTableInfo(
            std::vector <std::string> id_str,
            std::vector <std::string> status_str,
            std::vector <std::string> progress_str,
            std::vector<bool> is_finished);

    void updateInfo(int id, std::string id_str, std::string status_str, bool is_finished);

    void updateProgress(int id, std::string progress_str);
};


#endif //SO2_P2_PRINTER_H