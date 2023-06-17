#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Gui.h"
#include "../TaskManager/TaskManager.h"
#include "../TaskManager/Category.h"
#include "../TaskManager/Note.h"
#include "../TaskManager/Task.h"
#include "../TaskManager/User.h"
#include "sqlite/sqlite3.h"


class QDialog; // Forward declaration of QDialog


class Gui : public QMainWindow
{
    Q_OBJECT

public:
    Gui(QWidget *parent = nullptr);
    ~Gui();

private:
    Ui::GuiClass ui;
    TaskManager taskManager;
    QString defaultCategory;
    QWidget* TaskCreateWidget;

private slots:
    void handleCreateTaskButtonClicked(); // Declare the slot function

    void handlePrintAllTasksButtonClicked();
    void handleTaskListItemClicked(QListWidgetItem* item);

    void handleAddButtonClicked();
    void handleCancelButtonClicked();
   // void editTaskButtonClicked();
   // void editTask(Task* task);
    void openTaskEditDialog(Task* task);
    void handleSortComboBoxIndexChanged(int index);
};
