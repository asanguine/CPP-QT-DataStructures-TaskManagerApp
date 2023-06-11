#include "Note.h"



Note::Note(std::string _text,
    std::string _author,
    std::string _timestamp) : text(_text),
                            author(_author),
                            timestamp(_timestamp) {};



void Note::displayNote() {
    std::cout << text << std::endl;
}