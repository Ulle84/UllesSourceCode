#ifndef CONVERTER_H
#define CONVERTER_H

#include <QString>

class Converter
{
public:
    static QString intToQString(int number);
    static QString prizeToString(double prize);
};

#endif // CONVERTER_H
