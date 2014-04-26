#include <QApplication>
#include "TimeCalculator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TimeCalculator w;
    w.show();
    
    return a.exec();
}
