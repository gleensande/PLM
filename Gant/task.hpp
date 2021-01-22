#pragma once
#include <string>
#include <iostream>

class Task {
 private:
    std::string task_name;
    int start_time;
    int end_time;
    int weight;
 public:
    void create(std::string _task_name, int _start_time, int _end_time);
    void print();
    int get_start_time();
    int get_end_time();
    int get_weight();
    int get_reverse_weight();
};