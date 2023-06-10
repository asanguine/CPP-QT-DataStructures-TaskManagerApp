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
      //Constructors and getters / setters for category properties.
      //Functions to manage tasks within the category(e.g., addTask, removeTask).
    Category(std::string _name = "");

    ~Category() {};


};

