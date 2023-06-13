#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Gui.h"
#include "../TaskManager/TaskManager.h"
#include "../TaskManager/Category.h"
#include "../TaskManager/Note.h"
#include "../TaskManager/Task.h"
#include "../TaskManager/User.h"


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

private slots:
    void handleCreateTaskButtonClicked(); // Declare the slot function

    void handlePrintAllTasksButtonClicked();
    void handleTaskListItemClicked(QListWidgetItem* item);
};
