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
    //Constructors and functions to manage categories(e.g., addCategory, removeCategory).
    //Functions to manage tasks across categories(e.g., createTask, updateTask, deleteTask).
    
    TaskManager();

    ~TaskManager() {};
};

