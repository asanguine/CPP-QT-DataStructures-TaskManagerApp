#include "Gui.h"
#include <QtWidgets/QApplication>

#include "../TaskManager/TaskManager.h"
#include "../TaskManager/Category.h"
#include "../TaskManager/Note.h"
#include "../TaskManager/Task.h"
#include "../TaskManager/User.h"

/*
██████╗  ██╗   ██╗██╗
██╔════╝ ██║   ██║██║
██║  ███╗██║   ██║██║
██║   ██║██║   ██║██║
╚██████╔╝╚██████╔╝██║
╚═════╝  ╚═════╝  ╚═╝
*/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gui w;
    w.show();
    return a.exec();
}
