#include "TaskManager.h"



TaskManager::TaskManager() : allTasks(){
	categories = std::vector<Category>();
	initializeDatabase();
	loadTasksFromDatabase();
}


void TaskManager::addCategory(const Category& category) {
	for (const auto& c : categories) {
		if (c.getCategoryName() == category.getCategoryName()) {
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
		if (c.getCategoryName() == categoryName) {//name of category
			std::cout << c.getCategoryName() << std::endl;
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

std::vector<std::string> TaskManager::getAllCategoryNames() const {
	std::vector<std::string> categoryNames;
	for (const Category& category : categories) {
		categoryNames.push_back(category.getCategoryName());
	}
	return categoryNames;
}

void TaskManager::displayTasksByCategory(const std::string& categoryName) {
	Category* category = getCategoryByName(categoryName);
	if (category == nullptr) {
		std::cout << "Category not found." << std::endl;
		return;
	}
	std::cout << "Tasks in category \n" << category->getCategoryName() << "\":" << std::endl;
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


void TaskManager::editTask(const std::string& taskName, const Task& newTask) {
	for (Task& task : allTasks) {
		if (task.getTaskTitle() == taskName) {
			task = newTask;
			std::cout << "Task '" << taskName << "' has been updated." << std::endl;
			updateDatabase(); // Update the database
			return;
		}
	}
	std::cout << "Task '" << taskName << "' does not exist." << std::endl;
}



void TaskManager::markAsCompleted(const std::string& taskName) {
	for (Task& task : allTasks) {
		if (task.getTaskTitle() == taskName) {
			task.setCompleted(true);
			std::cout << taskName << " marked as completed" << std::endl;

			updateDatabase(); /// DATABASE

			return;
		}
	}
	std::cout << "Task: " << taskName << " not found." << std::endl;
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
	
	updateDatabase(); /// DATABASE
}


void TaskManager::removeTask(const std::string& taskname) {
	for (const Task& task : allTasks) {
		if (task.getTaskTitle() == taskname) {
			allTasks.erase(std::remove(allTasks.begin(), allTasks.end(), task), allTasks.end());
			std::cout << "task: " << taskname << " removed\nshame on you!" << std::endl;
			
			updateDatabase(); /// DATABASE
		}
	}
	std::cout << "Task: " << taskname << " not found." << std::endl;
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




/// DATABASE PART

void TaskManager::loadTasksFromDatabase() {
	sqlite3* db;
	int rc = sqlite3_open("tasks.db", &db);

	if (rc) {
		// Handle the error
		std::cerr << "Cannot open the database: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}

	const char* sql = "SELECT * FROM tasks;";
	sqlite3_stmt* stmt;

	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		// Handle the error
		std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		const unsigned char* title = sqlite3_column_text(stmt, 1);
		const unsigned char* description = sqlite3_column_text(stmt, 2);
		int priority = sqlite3_column_int(stmt, 3);
		const unsigned char* dueDate = sqlite3_column_text(stmt, 4);
		const unsigned char* category = sqlite3_column_text(stmt, 5);
		int completed = sqlite3_column_int(stmt, 6);

		std::string titleStr(reinterpret_cast<const char*>(title));
		std::string descriptionStr(reinterpret_cast<const char*>(description));
		std::string dueDateStr(reinterpret_cast<const char*>(dueDate));
		std::string categoryStr(reinterpret_cast<const char*>(category));

		Task task(titleStr, descriptionStr, priority, dueDateStr, categoryStr, completed);
		allTasks.push_back(task);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void TaskManager::initializeDatabase() {
	sqlite3* db;
	int rc = sqlite3_open("tasks.db", &db);

	if (rc) {
		// Handle the error
		std::cerr << "Cannot open the database: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}

	const char* sql = "CREATE TABLE IF NOT EXISTS tasks ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"title TEXT NOT NULL,"
		"description TEXT,"
		"priority INTEGER,"
		"due_date TEXT,"
		"category TEXT,"
		"completed INTEGER"
		"CREATE TABLE IF NOT EXISTS categories ("
		"name TEXT PRIMARY KEY"
		");";

	char* errMsg;
	rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
	if (rc != SQLITE_OK) {
		// Handle the error
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		sqlite3_close(db);
		return;
	}

	sqlite3_close(db);
}

void TaskManager::updateDatabase() {
	sqlite3* db;
	int rc = sqlite3_open("tasks.db", &db);

	if (rc) {
		// Handle the error
		std::cerr << "Cannot open the database: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return;
	}

	// Clear the existing tasks in the database
	std::string clearSql = "DELETE FROM tasks;";
	char* errMsg;
	rc = sqlite3_exec(db, clearSql.c_str(), nullptr, nullptr, &errMsg);
	if (rc != SQLITE_OK) {
		// Handle the error
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		sqlite3_close(db);
		return;
	}

	// Insert the updated tasks from the allTasks vector
	for (const Task& task : allTasks) {
		std::string completedValue = task.isCompleted() ? "1" : "0";
		std::string sql = "INSERT INTO tasks (title, description, priority, due_date, category, completed) VALUES ('" +
			task.getTaskTitle() + "', '" + task.getTaskDescription() + "', " +
			std::to_string(task.getPriority()) + ", '" + task.getDueDate() + "', '" +
			task.getTaskCategory() + "', " + completedValue + ");";

		rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
		if (rc != SQLITE_OK) {
			// Handle the error
			std::cerr << "SQL error: " << errMsg << std::endl;
			sqlite3_free(errMsg);
		}
	}

	sqlite3_close(db);
}
