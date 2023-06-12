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
         int _priority = 0,
        std::string _dueDate = "00/00/0000",
         std::string _category = "",
         bool _completed = false);

    ~Task() {};

    std::string getTaskTitle() const;
    void markAsCompleted();
    void updatePriority(int newPriority);
    void displayTaskDetails();
    void setCompleted(bool setCompleted);
    bool isCompleted() const;
    int getPriority() const;
    int GetdueDateAsInteger();


    bool operator==(const Task& other) const;
    friend inline std::ostream& operator<<(std::ostream& os, const Task& task);
};




inline std::ostream& operator<<(std::ostream& os, const Task& task) {
    os << "Task title: " << task.title << std::endl;
    os << "description: " << task.description << std::endl;
    os << "priority: " << task.priority << std::endl;
    os << "due date: " << task.dueDate << std::endl;
    os << "completion: " << task.completed << std::endl;
    os << "category: " << task.category << std::endl;
    return os;
}
