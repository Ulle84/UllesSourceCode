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

QString Converter::prizeToString(double prize)
{
    QString string = QString::number(prize, 'f', 2).replace('.', ',');

    if (prize < 100)
    {
        string.prepend(" ");
    }

    if (prize < 10)
    {
        string.prepend(" ");
    }

    return string;
}
