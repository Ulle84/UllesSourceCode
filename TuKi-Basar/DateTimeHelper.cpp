#include <QDate>
#include <QDateTime>

#include "DateTimeHelper.h"

QString DateTimeHelper::getCurrentDate()
{
    return QDate::currentDate().toString("yyyy-MM-dd");
}

QString DateTimeHelper::getCurrentDateAndTime()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}
