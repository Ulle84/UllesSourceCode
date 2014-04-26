#include <QApplication>
#include "ReadRawImage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReadRawImage w;
    w.show();
    
    return a.exec();
}
