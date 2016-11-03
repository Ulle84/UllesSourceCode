#ifndef INCLUDEFINDER_H
#define INCLUDEFINDER_H

#include <QString>
#include <QStringList>


class IncludeFinder
{
public:
  IncludeFinder();

  QStringList files(const QString& directory, const QStringList& includes);

private:
  QStringList m_extensions;
};

#endif // INCLUDEFINDER_H
