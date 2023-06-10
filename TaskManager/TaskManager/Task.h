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


public:

    //Constructors and getters / setters for task properties.
    //Functions to manipulate notes(e.g., addNote, removeNote).
    Task(std::string _title = "",
         std::string _description = "",
         std::string _category = "",
         int _priority = 0,
         bool _completed = false);

    ~Task() {};





};

