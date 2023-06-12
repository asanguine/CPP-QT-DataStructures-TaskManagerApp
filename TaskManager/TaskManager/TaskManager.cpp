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
	/*for (auto catToRmv = categories.begin(); catToRmv != categories.end(); ++catToRmv) {
		if (*catToRmv == category) {
			categories.erase(catToRmv);
		}
	}*/
	///this is new better way for removing from vector.
	categories.erase(std::remove(categories.begin(), categories.end(), category), categories.end());
	for (const Task& task : category.getTasks()) {
		allTasks.erase(std::remove(allTasks.begin(), allTasks.end(), task), allTasks.end());
	}
}


Category* TaskManager::getCategoryByName(const std::string& categoryName) {
	for (const Category& c : categories) {
		if (c.getName() == categoryName) {//name of category
			std::cout << c.getName() << std::endl;
			//return &c;
			return const_cast <Category*>(&c);
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


void TaskManager::displayAllTasks(){
	for (const Task& task : allTasks) {
		std::cout << task << std::endl;
	}
}


std::vector<Task>& TaskManager::getAllTasks() {
	return allTasks;
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



void TaskManager::addTaskToCategory(const std::string& categoryName, const Task& task) {
	Category* category = getCategoryByName(categoryName);
	if (category == nullptr) {
		std::cout << "Category not found." << std::endl;
		return;
	}
	category->addTask(task);
	allTasks.push_back(task);
}



void TaskManager::removeTaskFromCategory(const std::string& categoryName, const std::string& taskName) {
	Category* category = getCategoryByName(categoryName);
	if (category == nullptr) {
		std::cout << "Category not found." << std::endl;
		return;
	}

	Task* task = category->getTaskByName(taskName);
	if (task == nullptr) {
		std::cout << "Task not found in the category." << std::endl;
		return;
	}

	category->removeTask(*task);
	allTasks.erase(std::remove(allTasks.begin(), allTasks.end(), *task), allTasks.end());
	std::cout << "Task removed successfully." << std::endl;
}


void TaskManager::editTask(const std::string& categoryName, const std::string& taskName, const Task& newTask) {
	Category* category = getCategoryByName(categoryName);
	if (category) {
		Task* task = category->getTaskByName(taskName);
		if (task) {
			*task = newTask;
			std::cout << "Task '" << taskName << "' has been updated." << std::endl;
		}
		else {
			std::cout << "Task '" << taskName << "' does not exist." << std::endl;
		}
	}
	else {
		std::cout << "Category '" << categoryName << "' does not exist." << std::endl;
	}
}



void TaskManager::markAsCompleted(const std::string& taskName) {
	for (Task& task : allTasks) {
		if (task.getTaskTitle() == taskName) {
			task.setCompleted(true);
			std::cout << taskName << " marked as completed" << std::endl;
			return;
		}
	}
	
}




void TaskManager::mergeSort(std::vector<Task>& tasks) {
	int n; n = tasks.size();
	if (n < 2) return;

	int mid = n / 2;
	std::vector<Task> left(mid);
	std::vector<Task> right(n - mid);

	for (int i = 0; i < mid; i++) {
		left[i] = tasks[i];
	}
	for (int i = mid; i < n; i++) {
		right[i - mid] = tasks[i];
	}
	mergeSort(left);
	mergeSort(right);
	mergePriority(left, right, tasks);
}


void TaskManager::mergePriority(std::vector<Task>& left, std::vector<Task>& right, std::vector<Task>& tasks) {
	int leftsize = left.size();
	int rightsize = right.size();
	int l = 0, r = 0, i = 0;

	while (l < leftsize && r < rightsize) {
		if (left[l].getPriority() >= right[r].getPriority()) {
			tasks[i] = left[l];
			l++;
		}
		else {
			tasks[i] = right[r];
			r++;
		}
		i++;
	}
	while (l < leftsize) {
		tasks[i] = left[l];
		l++;
		i++;
	}
	while (r < rightsize) {
		tasks[i] = right[r];
		r++;
		i++;
	}
}


void TaskManager::mergeDueDate(std::vector<Task>& left, std::vector<Task>& right, std::vector<Task>& tasks) {
	int leftsize = left.size();
	int rightsize = right.size();
	int l = 0, r = 0, i = 0;

	while (l < leftsize && r < rightsize) {
		if (left[l].GetdueDateAsInteger() <= right[r].GetdueDateAsInteger()) {
			tasks[i] = left[l];
			l++;
		}
		else {
			tasks[i] = right[r];
			r++;
		}
		i++;
	}
	while (l < leftsize) {
		tasks[i] = left[l];
		l++;
		i++;
	}
	while (r < rightsize) {
		tasks[i] = right[r];
		r++;
		i++;
	}
}