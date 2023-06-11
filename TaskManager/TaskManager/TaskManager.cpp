#include "TaskManager.h"




TaskManager::TaskManager() {
	categories = std::vector<Category>();
}


void TaskManager::addCategory(const Category& category) {
	for (const auto& c : categories) {
		if (c.getName() == category.getName()) {
			std::cout << "same category already exists..." << std::endl;
			return;
		}
	}
	categories.push_back(category);
}



void TaskManager::removeCategory(const Category& category) {
	for (auto catToRmv = categories.begin(); catToRmv != categories.end(); ++catToRmv) {
		if (*catToRmv == category) {
			categories.erase(catToRmv);
		}
	}
}


Category* TaskManager::getCategoryByName(const std::string& categoryName) {
	for (auto& c : categories) {
		if (c.getName() == categoryName) {//name of category
			std::cout << c.getName() << std::endl;
			return &c;
		}
	}
	return nullptr;
}


void TaskManager::displayCategories() const{
	for (const auto& c : categories) {
		std::cout << c << std::endl;
	}
}


void TaskManager::displayTasksByCategory(const std::string& categoryName) {
	Category* category = getCategoryByName(categoryName);
	if (category == nullptr) {
		std::cout << "Category not found." << std::endl;
		return;
	}
	std::cout << "Tasks in category \n" << category->getName() << "\":" << std::endl;
	category->displayTasks();
}


void TaskManager::displayCompletedTasks() {
	for (const Category& category : categories) {
		for (const Task& task : category.getTasks()) {
			if (task.isCompleted()) {
				std::cout << task << std::endl;
			}
		}
	}
}


void TaskManager::displayPendingTasks() {
	for (const Category& category : categories) {
		for (const Task& task : category.getTasks()) {
			if (!task.isCompleted()) {
				std::cout << task << std::endl;
			}
		}
	}
}
