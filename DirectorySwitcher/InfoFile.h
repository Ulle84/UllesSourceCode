#ifndef INFOFILE_H
#define INFOFILE_H

#include <QString>

class InfoFile
{
public:
  InfoFile();
  InfoFile(const QString& path);

  QString path();
  void setPath(const QString& path);

  QString id();
  void setId(const QString& id);

  QString content();
  void setContent(const QString& content);

  bool writeToFile();

private:
  bool readFromFile();

  QString m_path;
  QString m_id;
  QString m_content;
};

#endif // INFOFILE_H
