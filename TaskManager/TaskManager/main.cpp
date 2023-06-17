#include <iostream>
#include "TaskManager.h"
#include "Category.h"
#include "Note.h"
#include "Task.h"
#include "User.h"






int main()
{


	/*
	std::cout << 
		"		██████╗ ██╗██████╗ ██╗  ██╗ █████╗ ███╗   ██╗███████╗\n"
		"		██╔══██╗██║██╔══██╗██║ ██╔╝██╔══██╗████╗  ██║██╔════╝\n"
		"		██████╔╝██║██████╔╝█████╔╝ ███████║██╔██╗ ██║███████╗\n"
		"		██╔══██╗██║██╔══██╗██╔═██╗ ██╔══██║██║╚██╗██║╚════██║\n"
		"		██████╔╝██║██║  ██║██║  ██╗██║  ██║██║ ╚████║███████║\n"
		"		╚═════╝ ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚══════╝\n"

		"  	 ████████╗ █████╗ ███████╗██╗  ██╗    ███╗   ███╗ █████╗ ███╗   ██╗ █████╗  ██████╗ ███████╗██████╗ \n"
		"	 ╚══██╔══╝██╔══██╗██╔════╝██║ ██╔╝    ████╗ ████║██╔══██╗████╗  ██║██╔══██╗██╔════╝ ██╔════╝██╔══██╗\n"
		"	   	██║   ███████║███████╗█████╔╝     ██╔████╔██║███████║██╔██╗ ██║███████║██║  ███╗█████╗  ██████╔╝\n"
		"		██║   ██╔══██║╚════██║██╔═██╗     ██║╚██╔╝██║██╔══██║██║╚██╗██║██╔══██║██║   ██║██╔══╝  ██╔══██╗\n"
		"		██║   ██║  ██║███████║██║  ██╗    ██║ ╚═╝ ██║██║  ██║██║ ╚████║██║  ██║╚██████╔╝███████╗██║  ██║\n"
		"		╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝    ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝\n"

		 << std::endl;
	
	*/
	TaskManager taskManager;

	 
	std::cout << "\nTest adding categories\n" << std::endl;
	taskManager.addCategory(Category("Category 1"));
	taskManager.addCategory(Category("Category 2"));
	taskManager.addCategory(Category("Category 3"));

	
	std::cout << "\n// Test adding tasks to categories\n" << std::endl;
	Task task1("Task 1", "Description 1", 1, "01/02/2023");
	Task task2("Task 2", "Description 2", 6, "02/02/2023");
	Task task3("Task 3", "Description 3", 5, "03/02/2023");
	Task task4("Task 4", "Description 4", 2, "01/01/2023");
	Task task5("Task 5", "Description 5", 10, "02/03/2023");
	Task task6("Task 6", "Description 6", 8, "03/01/2023");
	taskManager.addTaskToCategory("Category 1", task1);
	taskManager.addTaskToCategory("Category 2", task2);
	taskManager.addTaskToCategory("Category 3", task3);
	taskManager.addTaskToCategory("Category 1", task4);
	taskManager.addTaskToCategory("Category 2", task5);
	taskManager.addTaskToCategory("Category 3", task6);

	
	std::cout << "\n// Test displaying categories and tasks\n" << std::endl;
	taskManager.displayCategories();
	taskManager.displayTasksByCategory("Category 1");

	
	std::cout << "\n// Test removing tasks from categories\n" << std::endl;
	//taskManager.removeTaskFromCategory("Category 1", "Task 1");



	std::cout << "\n// displayting all tasks\n" << std::endl;
	taskManager.displayAllTasks();




	std::cout << "\n=========================\n" << std::endl;

	std::cout << "\n// displaying in order of priority:\n" << std::endl;
	taskManager.mergeSortPriority(taskManager.getAllTasks());
	taskManager.displayAllTasks();

	std::cout << "\n// displaying in order of duedate:\n" << std::endl;
	taskManager.mergeSortDueDate(taskManager.getAllTasks());
	taskManager.displayAllTasks();

	std::cout << "\n=========================\n" << std::endl;




	std::cout << "\n// Test marking tasks as completed\n" << std::endl;
	taskManager.markAsCompleted("Task 2");

	
	std::cout << "\n// Test displaying completed and pending tasks\n" << std::endl;
	taskManager.displayCompletedTasks();
	taskManager.displayPendingTasks();


	return 0;
}
