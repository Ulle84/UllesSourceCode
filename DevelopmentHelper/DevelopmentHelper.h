#ifndef DEVELOPMENTHELPER_H
#define DEVELOPMENTHELPER_H

#include <QMainWindow>

namespace Ui {
class DevelopmentHelper;
}

class QSettings;
class LogFileViewer;
class StashHelper;

class DevelopmentHelper : public QMainWindow
{
  Q_OBJECT

public:
  explicit DevelopmentHelper(QWidget *parent = 0);
  ~DevelopmentHelper();

private:
  Ui::DevelopmentHelper *ui;
  StashHelper* m_stashHelper;
  LogFileViewer* m_logFileViewer;
  QSettings* m_settings;
};

#endif // DEVELOPMENTHELPER_H
