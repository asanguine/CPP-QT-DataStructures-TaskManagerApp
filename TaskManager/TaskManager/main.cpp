#include <iostream>
#include "TaskManager.h"
#include "Category.h"
#include "Note.h"
#include "Task.h"
#include "User.h"






int main()
{
	//TaskManager tm;

	////Category cat1("cat1");

	//Task task1("yap", "bunu yap", "cat", 4, false, "00/00/0000");
	//Task task2("et", "bunu et", "kat", 3, false, "00/00/0000");

	//tm.addCategory(Category("catt1"));
	//tm.addCategory(Category("catt2"));
	//tm.addTaskToCategory("catt1", task1);
	//tm.addTaskToCategory("catt1", task2);
	//tm.displayCategories();
	//tm.displayPendingTasks();
	//tm.markAsCompleted("catt1", "yap");
	//tm.displayCompletedTasks();

	TaskManager taskManager;

	 
	std::cout << "\nTest adding categories\n" << std::endl;
	taskManager.addCategory(Category("Category 1"));
	taskManager.addCategory(Category("Category 2"));
	taskManager.addCategory(Category("Category 3"));

	
	std::cout << "\n// Test adding tasks to categories\n" << std::endl;
	Task task1("Task 1", "Description 1");
	Task task2("Task 2", "Description 2");
	Task task3("Task 3", "Description 3");
	taskManager.addTaskToCategory("Category 1", task1);
	taskManager.addTaskToCategory("Category 2", task2);
	taskManager.addTaskToCategory("Category 3", task3);

	
	std::cout << "\n// Test displaying categories and tasks\n" << std::endl;
	taskManager.displayCategories();
	taskManager.displayTasksByCategory("Category 1");

	
	std::cout << "\n// Test removing tasks from categories\n" << std::endl;
	taskManager.removeTaskFromCategory("Category 1", "Task 1");

	
	std::cout << "\n// Test marking tasks as completed\n" << std::endl;
	taskManager.markAsCompleted("Task 2");

	
	std::cout << "\n// Test displaying completed and pending tasks\n" << std::endl;
	taskManager.displayCompletedTasks();
	taskManager.displayPendingTasks();


	return 0;
}
