#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Task.h"

class Category
{

private:
    std::string name;
    std::vector<Task> tasks; // A collection of tasks belonging to the category.

public:

    Category(std::string _name = "");
    ~Category() {};


    std::string getName() const;
    void addTask(const Task& task);
    void removeTask(const Task & task);
    Task* getTaskByName(const std::string& taskName) const;
    void displayTasks();
    const std::vector<Task>& getTasks() const;

    bool operator==(const Category& other) const;
    friend inline std::ostream& operator<<(std::ostream& os, const Category& c);
};


inline std::ostream& operator<<(std::ostream& os, const Category& c) {
    os << c.getName() << std::endl;
    return os;
}