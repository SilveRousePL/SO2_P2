//
// Created by darek on 10.04.19.
//

#include "Printer.h"

Printer::Printer(TableChannel &channel) : channel(channel) {
    status = "Press SPACE to end                   ";
}

Printer::~Printer() {
    endwin();
}

void Printer::start() {
    bool finished = false;
    while (!finished) {
        timeout(1);
        int option = getch();
        if (option == ' ') {
            channel.dinner_finished = true;
            status = "Finishing...                         ";
        }
        if (channel.dinner_finished == true) {
            bool all_finished = true;
            for (auto item : philosopher_finished) {
                if (item == false) {
                    all_finished = false;
                    break;
                }
            }
            if (all_finished) {
                finished = true;
                status = "Finished!                            ";
            }
        }

        for (auto i = 0; i < philosopher_id.size(); ++i) {
            auto pos = i;
            auto y = 0;
            std::string row =
                    philosopher_id[i] + "\t" + philosopher_progress[i] + "\t" + philosopher_status[i];
            mvprintw(pos, y, row.c_str());
        }
        mvprintw(philosopher_id.size() + 1, 1, status.c_str());
        mvprintw(philosopher_id.size() + 3, 0, " ");
        refresh();
        if (finished) std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

void Printer::initTableInfo(
        std::vector <std::string> id_str,
        std::vector <std::string> status_str,
        std::vector <std::string> progress_str,
        std::vector<bool> is_finished) {
    philosopher_id = id_str;
    philosopher_status = status_str;
    philosopher_progress = progress_str;
    philosopher_finished = is_finished;

    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, true);
    use_default_colors();
}

void Printer::updateInfo(int id, std::string id_str, std::string status_str, bool is_finished) {
    philosopher_id[id] = id_str;
    philosopher_status[id] = status_str;
    philosopher_finished[id] = is_finished;
}

void Printer::updateProgress(int id, std::string progress_str) {
    philosopher_progress[id] = progress_str;
}