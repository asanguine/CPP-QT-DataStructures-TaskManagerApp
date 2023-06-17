#include "Gui.h"
#include <QDialog> // Include the header for QDialog
#include <QMessageBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>

Gui::Gui(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    defaultCategory = "Default Category";
    ui.categoryComboBox->addItem(defaultCategory);

    connect(ui.createTaskButton, &QPushButton::clicked, this, &Gui::handleCreateTaskButtonClicked);
    connect(ui.printAllTasksButton, &QPushButton::clicked, this, &Gui::handlePrintAllTasksButtonClicked);
    connect(ui.taskListWidget, &QListWidget::itemClicked, this, &Gui::handleTaskListItemClicked);
    
    connect(ui.addButton, &QPushButton::clicked, this, &Gui::handleAddButtonClicked);
    connect(ui.cancelButton, &QPushButton::clicked, this, &Gui::handleCancelButtonClicked);

    connect(ui.sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Gui::handleSortComboBoxIndexChanged);
    ui.sortComboBox->addItem("By Due Date");
    ui.sortComboBox->addItem("By Priority");
    ui.sortComboBox->setPlaceholderText("Sort by");

    ui.titleLineEdit->setPlaceholderText("Title");
    ui.descriptionLineEdit->setPlaceholderText("Description");
    ui.dueDateLineEdit->setPlaceholderText("Due date");

    //TaskCreateWidget = findChild<QWidget*>("TaskCreateWidget");
    TaskCreateWidget = ui.TaskCreateWidget->parentWidget();
    TaskCreateWidget->setVisible(false);

    ui.printAllTasksButton->setVisible(false);
    
    handlePrintAllTasksButtonClicked();
}



Gui::~Gui()
{}


void Gui::handleCreateTaskButtonClicked()
{
    TaskCreateWidget->setVisible(!TaskCreateWidget->isVisible());
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

        // Create the "Remove Task" button
        QPushButton* removeTaskButton = new QPushButton("Remove Task");
        connect(removeTaskButton, &QPushButton::clicked, [=]() {
            // Remove the task when the button is clicked
            taskManager.removeTask(task->getTaskTitle());
            //updateTaskList();
            handlePrintAllTasksButtonClicked();
            taskDialog->close();
            });

        // Create the "Edit Task" button
        QPushButton* editTaskButton = new QPushButton("Edit Task");
        connect(editTaskButton, &QPushButton::clicked, [=]() {
            // Open the task edit dialog
            openTaskEditDialog(task);
            taskDialog->close();
            });

        layout->addWidget(editTaskButton);

        // Add labels and buttons to the dialog layout
        layout->addWidget(titleLabel);
        layout->addWidget(descriptionLabel);
        layout->addWidget(priorityLabel);
        layout->addWidget(dueDateLabel);
        layout->addWidget(categoryLabel);
        layout->addWidget(removeTaskButton);
        layout->addWidget(editTaskButton);

        // Set the dialog layout and display it
        taskDialog->setLayout(layout);
        taskDialog->exec();
    }
}


void Gui::openTaskEditDialog(Task* task)
{
    // Create a new dialog for editing the task details
    QDialog* editDialog = new QDialog(this);
    QVBoxLayout* layout = new QVBoxLayout(editDialog);

    // Create the input fields for editing the task details
    QLineEdit* titleLineEdit = new QLineEdit(QString::fromStdString(task->getTaskTitle()));
    QLineEdit* descriptionLineEdit = new QLineEdit(QString::fromStdString(task->getTaskDescription()));
    QSpinBox* prioritySpinBox = new QSpinBox();
    prioritySpinBox->setValue(task->getPriority());
    QLineEdit* dueDateLineEdit = new QLineEdit(QString::fromStdString(task->getDueDate()));
    QComboBox* categoryComboBox = new QComboBox();

    // Set a default category
    const QString defaultCategory = "Default Category";
    categoryComboBox->addItem(defaultCategory);
    categoryComboBox->setCurrentText(defaultCategory);

    // Get the list of available categories
    std::vector<std::string> categories = taskManager.getAllCategoryNames();

    // Add the categories to the combobox
    for (const std::string& category : categories) {
        categoryComboBox->addItem(QString::fromStdString(category));
    }

    // Create the "Save" button
    QPushButton* saveButton = new QPushButton("Save");
    connect(saveButton, &QPushButton::clicked, [=]() {
        // Retrieve the updated values from the input fields/widgets
        const QString newTitle = titleLineEdit->text();
        const QString newDescription = descriptionLineEdit->text();
        const int newPriority = prioritySpinBox->value();
        const QString newDueDate = dueDateLineEdit->text();
        const QString newCategory = categoryComboBox->currentText();

        // Create a new Task object with the updated details
        Task newTask(newTitle.toStdString(), newDescription.toStdString(), newPriority, newDueDate.toStdString(), newCategory.toStdString());

        // Update the task in the task manager
        taskManager.editTask(task->getTaskTitle(), newTask);

        // Update the task list
        //updateTaskList();
        handlePrintAllTasksButtonClicked();
        editDialog->close();
        });

    layout->addWidget(titleLineEdit);
    layout->addWidget(descriptionLineEdit);
    layout->addWidget(prioritySpinBox);
    layout->addWidget(dueDateLineEdit);
    layout->addWidget(categoryComboBox);
    layout->addWidget(saveButton);

    editDialog->setLayout(layout);
    editDialog->exec();
}




void Gui::handleAddButtonClicked()
{
    // Retrieve the values from the input fields/widgets
    const QString title = ui.titleLineEdit->text();
    const QString description = ui.descriptionLineEdit->text();
    const int priority = ui.prioritySpinBox->value();
    const QString dueDate = ui.dueDateLineEdit->text();
    const QString category = ui.categoryComboBox->currentText();

    taskManager.createTask(title.toStdString(), description.toStdString(), priority, dueDate.toStdString(), category.toStdString());

    // Clear the input fields
    ui.titleLineEdit->clear();
    ui.descriptionLineEdit->clear();
    ui.prioritySpinBox->setValue(0);
    ui.dueDateLineEdit->clear();
    ui.categoryComboBox->setCurrentIndex(0);

    // Hide the TaaskCreateWidget
    TaskCreateWidget->setVisible(false);
    handlePrintAllTasksButtonClicked();
}



void Gui::handleCancelButtonClicked()
{
    // Clear the input fields
    ui.titleLineEdit->clear();
    ui.descriptionLineEdit->clear();
    ui.prioritySpinBox->setValue(0);
    ui.dueDateLineEdit->clear();
    ui.categoryComboBox->setCurrentIndex(0);

    // Hide the TaaskCreateWidget
    TaskCreateWidget->setVisible(false);
}



void Gui::handleSortComboBoxIndexChanged(int index)
{
    QString selectedSortOption = ui.sortComboBox->currentText();
    std::vector<Task>& tasks = taskManager.getAllTasks();

    if (selectedSortOption == "By Priority") {
        taskManager.mergeSortPriority(tasks);
    }
    else if (selectedSortOption == "By Due Date") {
        taskManager.mergeSortDueDate(tasks);
    }

    handlePrintAllTasksButtonClicked();
}