#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Note.h"

class Task
{
private:
    std::string title;
    std::string description;
    std::string category;
    int priority;
    bool completed;
    std::vector<Note> notes;
    std::string dueDate;


public:


    Task(std::string _title = "",
         std::string _description = "",
         std::string _category = "",
         int _priority = 0,
         bool _completed = false,
         std::string _dueDate = "00/00/0000");

    ~Task() {};

    void markAsCompleted();
    void updatePriority(int newPriority);
    void displayTaskDetails();
    bool isCompleted() const;



    bool operator==(const Task& other) const;
    friend inline std::ostream& operator<<(std::ostream& os, const Task& task);
};




inline std::ostream& operator<<(std::ostream& os, const Task& task) {
    os << "Task title: " << task.title << std::endl;
    os << "due date: " << task.dueDate << std::endl;
    os << "description: " << task.description << std::endl;
    return os;
}










