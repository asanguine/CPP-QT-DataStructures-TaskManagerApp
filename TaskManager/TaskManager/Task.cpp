#include "Task.h"



Task::Task(std::string _title,
	std::string _description,
	std::string _category,
	int _priority,
	bool _completed) : title(_title),
						description(_description),
						category(_category),
						priority(_priority),
						completed(_completed) {}


