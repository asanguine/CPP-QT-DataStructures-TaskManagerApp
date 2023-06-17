#include "Gui.h"
#include <QDialog> // Include the header for QDialog
#include <QMessageBox>

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
    handlePrintAllTasksButtonClicked();
}



Gui::~Gui()
{}


void Gui::handleCreateTaskButtonClicked()
{
    TaskCreateWidget->setVisible(!TaskCreateWidget->isVisible());
    /*
    // Retrieve the values from the input fields/widgets
    const QString title = ui.titleLineEdit->text();
    const QString description = ui.descriptionLineEdit->text();
    const int priority = ui.prioritySpinBox->value();
    const QString dueDate = ui.dueDateLineEdit->text();
    const QString category = ui.categoryComboBox->currentText();

    taskManager.createTask(title.toStdString(), description.toStdString(), priority, dueDate.toStdString(), category.toStdString());
    */
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

        // Create the "Edit Task" button
        QPushButton* editButton = new QPushButton("Edit Task");
        QPushButton* removeTaskButton = new QPushButton("Remove Task");

        // Connect the "Remove Task" button to the removeTask function
        connect(removeTaskButton, &QPushButton::clicked, [this, taskDialog, task]() {
            taskManager.removeTask(task->getTaskTitle());
            handlePrintAllTasksButtonClicked();
            taskDialog->close();
            });

        // Connect the "Edit Task" button to the handleAddButtonClicked function with pre-filled values
        connect(editButton, &QPushButton::clicked, [this, taskDialog, task]() {
            handleAddButtonClicked();
            ui.titleLineEdit->setText(QString::fromStdString(task->getTaskTitle()));
            ui.descriptionLineEdit->setText(QString::fromStdString(task->getTaskDescription()));
            ui.prioritySpinBox->setValue(task->getPriority());
            ui.dueDateLineEdit->setText(QString::fromStdString(task->getDueDate()));
            ui.categoryComboBox->setCurrentText(QString::fromStdString(task->getTaskCategory()));
            taskDialog->close();
            });

        // Add labels and buttons to the dialog layout
        layout->addWidget(titleLabel);
        layout->addWidget(descriptionLabel);
        layout->addWidget(priorityLabel);
        layout->addWidget(dueDateLabel);
        layout->addWidget(categoryLabel);
        layout->addWidget(editButton);
        layout->addWidget(removeTaskButton);

        // Set the dialog layout and display it
        taskDialog->setLayout(layout);
        taskDialog->exec();

        // Clean up the dialog after it is closed
        taskDialog->deleteLater();
    }
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