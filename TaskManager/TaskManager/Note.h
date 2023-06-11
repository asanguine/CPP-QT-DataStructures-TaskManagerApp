#pragma once
#include <string>
#include <iostream>
#include <vector>


class Note
{

private:
    std::string text;
    std::string author;
    std::string timestamp;
    
public:
    Note(std::string _text = "",
        std::string _author = "",
        std::string _timestamp = "");

    ~Note() {};


    void displayNote();


};

