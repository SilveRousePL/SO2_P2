//
// Created by darek on 10.04.19.
//

#include "Philosopher.h"

Philosopher::Philosopher(int id, Fork &left, Fork &right, TableChannel &channel, Printer &printer)
        : id(id), channel(channel), left_fork(left), right_fork(right), thread(&Philosopher::live, this),
          printer(printer) {
}

void Philosopher::live() {
    channel.sync.wait();
    while (!channel.dinner_finished) {
        think();
        eat();
    }

    // End
    freeForks();
    setStatus(Status::FINISHED);
    if (thread.joinable())
        thread.detach();
}

void Philosopher::think() {
    setStatus(Status::THINKING);
    wait(2000, 3000);
}

void Philosopher::eat() {
    requestForks();
    std::lock(left_fork.getMutex(), right_fork.getMutex());
    std::lock_guard <std::mutex> left_lock(left_fork.getMutex(), std::adopt_lock);
    std::lock_guard <std::mutex> right_lock(right_fork.getMutex(), std::adopt_lock);
    setStatus(Status::EATING);
    wait(2000, 3000);
    freeForks();
    counter++;
}

void Philosopher::requestForks() {
    setStatus(Status::REQUESTING);
    left_fork.request(id);
    right_fork.request(id);
}

void Philosopher::freeForks() {
    left_fork.free();
    right_fork.free();
}

bool Philosopher::isFinished() {
    return status == Philosopher::FINISHED;
}

std::string Philosopher::printPhilosopher() {
    return "P:" + std::to_string(id) + " | I:" + std::to_string(counter);
}

std::string Philosopher::printStatus() {
    if (status == Philosopher::REQUESTING) return "Request for forks     ";
    if (status == Philosopher::THINKING) return "Thinking              ";
    if (status == Philosopher::EATING) return "Eating                ";
    if (status == Philosopher::FINISHED) return "Finished              ";
    return "                      ";
}

std::string Philosopher::printProgress() {
    int current = progress;
    int space = 25 - current - 1;
    std::string bar = "[";
    while (current--) bar += "#";
    while (space--) bar += " ";
    bar += "]";
    return bar;
}

void Philosopher::setStatus(Status status) {
    this->status = status;
    printer.updateInfo(id, printPhilosopher(), printStatus() + " " + left_fork.printStatus(), isFinished());
}

void Philosopher::wait(uint from, uint to) {
    int rand = (from + (random() % (to - from))) / 25;
    this->progress = 0;
    for (progress = 0; progress < 25; progress++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand));
        printer.updateInfo(id, printPhilosopher(), printStatus() + " " + left_fork.printStatus(), isFinished());
        printer.updateProgress(id, printProgress());
    }
    this->progress = 0;
}