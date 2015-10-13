#ifndef PROJECTRENAMER_H
#define PROJECTRENAMER_H

#include <QWidget>

namespace Ui
{
class ProjectRenamer;
}

class ProjectRenamer : public QWidget
{
  Q_OBJECT

public:
  explicit ProjectRenamer(QWidget* parent = 0);
  ~ProjectRenamer();

private:
  Ui::ProjectRenamer* ui;
};

#endif // PROJECTRENAMER_H
