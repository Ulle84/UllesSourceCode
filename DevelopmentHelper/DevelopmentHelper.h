#ifndef DEVELOPMENTHELPER_H
#define DEVELOPMENTHELPER_H

#include <QMainWindow>

namespace Ui {
class DevelopmentHelper;
}

class StashHelper;

class DevelopmentHelper : public QMainWindow
{
  Q_OBJECT

public:
  explicit DevelopmentHelper(QWidget *parent = 0);
  ~DevelopmentHelper();

private:
  Ui::DevelopmentHelper *ui;
  StashHelper* stashHelper;
};

#endif // DEVELOPMENTHELPER_H
