#include <QApplication>
#include "Widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    if (argc > 1)
    {
        QString fileName = argv[1];
        w.setFile(fileName);
    }


    w.show();
    
    return a.exec();
}
