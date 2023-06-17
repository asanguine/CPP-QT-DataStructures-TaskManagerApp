#include "Category.h"




Category::Category(std::string _name) : name(_name) {}




void Category::addTask(const Task& task) {
	tasks.push_back(task);
}


void Category::removeTask(const Task& task) {
	for (auto i = tasks.begin(); i != tasks.end(); ++i) {
		if (*i == task) {
			tasks.erase(i);
			std::cout << "task removed" << std::endl;
			return;
		}
	}
	std::cout << "Task not found in the category." << std::endl;
}


void Category::displayTasks() {
	for (const Task& t : tasks) {
		std::cout << t << std::endl;
	}
}



std::string Category::getCategoryName() const{
	return name;
}


const std::vector<Task>& Category::getTasks() const {
	return tasks;
}


Task* Category::getTaskByName(const std::string& taskName) const{
	for (const Task& task : tasks) {
		if (task.getTaskTitle() == taskName) {
			return const_cast<Task*>(&task);
		}
	}
	return nullptr;
	throw std::runtime_error("task not found");
}


bool Category::operator==(const Category& other) const {
	return (name == other.name);
}