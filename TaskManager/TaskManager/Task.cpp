#include "Task.h"



Task::Task(std::string _title,
	std::string _description,
	std::string _category,
	int _priority,
	bool _completed,
	std::string _dueDate) : title(_title),
							description(_description),
							category(_category),
							priority(_priority),
							completed(_completed),
							dueDate(_dueDate){}




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

bool Task::operator==(const Task& other) const {
	return (title == other.title &&
		description == other.description &&
		category == other.category &&
		priority == other.priority &&
		completed == other.completed &&
		dueDate == other.dueDate);
}