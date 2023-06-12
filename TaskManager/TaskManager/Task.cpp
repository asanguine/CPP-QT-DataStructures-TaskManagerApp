#include "Task.h"



Task::Task(std::string _title,
	std::string _description,
	int _priority,
	std::string _dueDate,
	std::string _category,
	bool _completed) : title(_title),
							description(_description),
							priority(_priority),
							dueDate(_dueDate),
							category(_category),
							completed(_completed){}


std::string Task::getTaskTitle() const {
	return title;
}


void Task::markAsCompleted() {
	completed = true;
}


void Task::updatePriority(int newPriority) {
	priority = newPriority;
}


void Task::displayTaskDetails() {
	std::cout << title << " | " << category << "\n" << description << std::endl;
}


bool Task::isCompleted() const {
	return completed;
}


void Task::setCompleted(bool setCompleted) {
	completed = setCompleted;
}


int Task::getPriority() const {
	return priority;
}


bool Task::operator==(const Task& other) const {
	return (title == other.title &&
		description == other.description &&
		priority == other.priority &&
		dueDate == other.dueDate &&
		category == other.category &&
		completed == other.completed);
}


int Task::GetdueDateAsInteger() {
	std::string dayString = dueDate.substr(0, 2);
	std::string monthString = dueDate.substr(3, 2);
	std::string yearString = dueDate.substr(6, 4);
	
	try {
		int day = std::stoi(dayString);
		int month = std::stoi(monthString);
		int year = std::stoi(yearString);
		int time = (day) + (month * 31) + (year * 366);
		return time;
	}
	catch (std::exception& e) {
		std::cout << "error at stoi conversion" << std::endl;
	}
}