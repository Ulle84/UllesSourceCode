#include "Converter.h"

QString Converter::intToQString(int number)
{
    QString string = QString::number(number);

    while(string.length() < 3)
    {
        string.prepend(" ");
    }

    return string;
}
