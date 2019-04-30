//
// Created by darek on 10.04.19.
//

#include <iostream>
#include "Table.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    int num = 5;
    if (argc >= 2) {
        try {
            num = (uint) std::stoi(argv[1]);
            if (num <= 1) {
                std::cerr << "Invalid parameter" << std::endl;
                return 1;
            }
        }
        catch (...) {
            std::cerr << "Invalid parameter" << std::endl;
            return 1;
        }
    }

    Table table(num);
    table.start();
    return 0;
}
