#ifndef PROJECTCLEANER_H
#define PROJECTCLEANER_H

#include <QString>
#include <QWidget>

class QSettings;

namespace Ui {
class ProjectCleaner;
}

class ProjectCleaner : public QWidget
{
  Q_OBJECT

public:
  explicit ProjectCleaner(QWidget *parent = 0);
  ~ProjectCleaner();

private slots:
  void on_pushButtonChooseDirectory_clicked();

private:
  Ui::ProjectCleaner *ui;

  QString m_directory;
  QSettings* m_settings;
};

#endif // PROJECTCLEANER_H
