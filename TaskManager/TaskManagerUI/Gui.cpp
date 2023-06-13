#include "Gui.h"
#include <QDialog> // Include the header for QDialog
#include <QMessageBox>

Gui::Gui(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    defaultCategory = "Default Category";
    ui.categoryComboBox->addItem(defaultCategory);
    // Connect the "Create Task" button
    connect(ui.createTaskButton, &QPushButton::clicked, this, &Gui::handleCreateTaskButtonClicked);

    // Print All Tasks" button connect
    connect(ui.printAllTasksButton, &QPushButton::clicked, this, &Gui::handlePrintAllTasksButtonClicked);

    // Connect the task list item click event
    connect(ui.taskListWidget, &QListWidget::itemClicked, this, &Gui::handleTaskListItemClicked);
}



Gui::~Gui()
{}


void Gui::handleCreateTaskButtonClicked()
{
    // Retrieve the values from the input fields/widgets
    const QString title = ui.titleLineEdit->text();
    const QString description = ui.descriptionLineEdit->text();
    const int priority = ui.prioritySpinBox->value();
    const QString dueDate = ui.dueDateLineEdit->text();
    const QString category = ui.categoryComboBox->currentText();

    /*
    if (category == defaultCategory) {
        // Display an error message or handle it appropriately
        QMessageBox::warning(this, "Error", "Please select a valid category.");
        return;
    }*/
    // Call the createTask function from your TaskManager object
    taskManager.createTask(title.toStdString(), description.toStdString(), priority, dueDate.toStdString(), category.toStdString());
}




void Gui::handlePrintAllTasksButtonClicked()
{
    // Clear the task list
    ui.taskListWidget->clear();

    // Retrieve the tasks from the task manager
    const std::vector<Task>& tasks = taskManager.getAllTasks();

    // Iterate over the tasks and add them to the list
    for (const Task& task : tasks) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(task.getTaskTitle()));
        ui.taskListWidget->addItem(item);
    }
}


void Gui::handleTaskListItemClicked(QListWidgetItem* item) {
    QString title = item->text();
    Task* task = taskManager.getTaskByTitle(title.toStdString());

    // Check if the task is valid
    if (task != nullptr) {
        // Create a new dialog to display the task details
        QDialog* taskDialog = new QDialog(this);
        QVBoxLayout* layout = new QVBoxLayout(taskDialog);

        // Create labels to display task details
        QLabel* titleLabel = new QLabel("Title: " + QString::fromStdString(task->getTaskTitle()));
        QLabel* descriptionLabel = new QLabel("Description: " + QString::fromStdString(task->getTaskDescription()));
        QLabel* priorityLabel = new QLabel("Priority: " + QString::number(task->getPriority()));
        QLabel* dueDateLabel = new QLabel("Due Date: " + QString::fromStdString(task->getDueDate()));
        QLabel* categoryLabel = new QLabel("Category: " + QString::fromStdString(task->getTaskCategory()));

        // Add labels to the dialog layout
        layout->addWidget(titleLabel);
        layout->addWidget(descriptionLabel);
        layout->addWidget(priorityLabel);
        layout->addWidget(dueDateLabel);
        layout->addWidget(categoryLabel);

        // Set the dialog layout and display it
        taskDialog->setLayout(layout);
        taskDialog->exec();
    }
}