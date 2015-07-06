#ifndef DEVELOPMENTHELPER_H
#define DEVELOPMENTHELPER_H

#include <QMainWindow>

namespace Ui {
class DevelopmentHelper;
}

class QSettings;
class LogFileViewer;
class StashHelper;
class CodeAssistant;
class ConverterBase64;
class DateTimeHelper;

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
  CodeAssistant* m_codeAssistant;
  ConverterBase64* m_converterBase64;
  DateTimeHelper* m_dateTimeHelper;
  QSettings* m_settings;
};

#endif // DEVELOPMENTHELPER_H
