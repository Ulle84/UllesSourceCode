#ifndef PROJECTCLEANERCONFIRMATION_H
#define PROJECTCLEANERCONFIRMATION_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class ProjectCleanerConfirmation;
}

class ProjectCleanerConfirmation : public QDialog
{
  Q_OBJECT

public:
  explicit ProjectCleanerConfirmation(QWidget *parent = 0);
  ~ProjectCleanerConfirmation();

  void setFilesToDelete(const QStringList& filesToDelete);

private:
  Ui::ProjectCleanerConfirmation *ui;
};

#endif // PROJECTCLEANERCONFIRMATION_H
