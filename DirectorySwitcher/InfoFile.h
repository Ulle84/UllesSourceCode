#ifndef INFOFILE_H
#define INFOFILE_H

#include <QString>

class InfoFile
{
public:
  InfoFile(const QString& path);

  QString id();
  QString content();

private:
  QString m_id;
  QString m_content;
};

#endif // INFOFILE_H
