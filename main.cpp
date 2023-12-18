#include "dragdropwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DragDropWidget myWidget;
    myWidget.resize(1200,900); // Ändert die Größe des Widgets auf 1200x900
    myWidget.show(); // Zeigt das Widget an

    return a.exec();
}
