#include "task.hpp"

void Task::create(std::string _task_name, int _start_time, int _end_time) {
    task_name = _task_name;
    start_time = _start_time;
    end_time = _end_time;
    weight = end_time - start_time;
}

void Task::print() {
    std::cout << "\"" <<  task_name << "\" (" << start_time << ", " << end_time << ")" << std::endl;
}

int Task::get_start_time() {
    return start_time;
}

int Task::get_end_time() {
    return end_time;
}

int Task::get_weight() {
    return weight;
}

int Task::get_reverse_weight() {
    return -weight;
}