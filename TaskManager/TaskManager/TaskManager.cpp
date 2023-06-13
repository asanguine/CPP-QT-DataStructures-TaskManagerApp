#include "TaskManager.h"




TaskManager::TaskManager() : allTasks(){
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



void TaskManager::createTask(const std::string& title,
								const std::string& description,
								const int& priority,
								const std::string& dueDate,
								const std::string& category) {
	Task task(title, description, priority, dueDate, category, false);
	allTasks.push_back(task);
	Category* cat = getCategoryByName(category);
	if (cat) {
		int index = allTasks.size() - 1; // Index of the newly created task
		cat->addTask(task);
	}
}


void TaskManager::removeTask(const std::string& taskname) {
	for (const Task& task : allTasks) {
		if (task.getTaskTitle() == taskname) {
			allTasks.erase(std::remove(allTasks.begin(), allTasks.end(), task), allTasks.end());
			std::cout << "task: " << taskname << " removed\nshame on you!" << std::endl;
		}
	}
}


Task* TaskManager::getTaskByTitle(const std::string& title) const {
	for (const Task& task : allTasks) {
		if (task.getTaskTitle() == title) {
			return const_cast<Task*>(&task);
			//return task;
		}
	}
	return nullptr;
}


void TaskManager::mergeSortPriority(std::vector<Task>& tasks) {
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
	mergeSortPriority(left);
	mergeSortPriority(right);
	mergePriority(left, right, tasks);
}

void TaskManager::mergeSortDueDate(std::vector<Task>& tasks) {
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
	mergeSortDueDate(left);
	mergeSortDueDate(right);
	mergeDueDate(left, right, tasks);
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


///try template for sorting functions
/*
template <typename Compare>
void TaskManager::mergeSort(std::vector<Task>& tasks, Compare comp) {
	int n = tasks.size();
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
	mergeSort(left, comp);
	mergeSort(right, comp);
	merge(left, right, tasks, comp);
}


template <typename Compare>
void TaskManager::merge(std::vector<Task>& left, std::vector<Task>& right, std::vector<Task>& tasks, Compare comp) {
	int leftSize = left.size();
	int rightSize = right.size();
	int l = 0, r = 0, i = 0;

	while (l < leftSize && r < rightSize) {
		if (comp(left[l], right[r])) {
			tasks[i] = left[l];
			l++;
		}
		else {
			tasks[i] = right[r];
			r++;
		}
		i++;
	}

	while (l < leftSize) {
		tasks[i] = left[l];
		l++;
		i++;
	}

	while (r < rightSize) {
		tasks[i] = right[r];
		r++;
		i++;
	}
}

*/

