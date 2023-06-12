#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Category.h"

class TaskManager
{

private:
    std::vector<Category> categories;
    std::vector<Task> allTasks;

public:

    
    TaskManager();

    ~TaskManager() {};


    void addCategory(const Category& category);
    void removeCategory(const Category& category);
    Category* getCategoryByName(const std::string& categoryName);
    void displayCategories() const;
    void displayTasksByCategory(const std::string& categoryName);
    void displayCompletedTasks();
    void displayPendingTasks();
    void addTaskToCategory(const std::string& categoryName, const Task& task);
    void removeTaskFromCategory(const std::string& categoryName, const std::string& taskName);
    
    void editTask(const std::string& categoryName, const std::string& taskName, const Task& newTask);
    void markAsCompleted(const std::string& taskName);
   
    void mergeSort(); //by priority
    void merge();

};

