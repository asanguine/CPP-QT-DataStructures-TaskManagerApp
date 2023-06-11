#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Category.h"

class TaskManager
{

private:
    std::vector<Category> categories;


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

};

