#ifndef DEVELOPMENTHELPER_H
#define DEVELOPMENTHELPER_H

#include <QMainWindow>
#include <QMap>
#include <QString>

namespace Ui {
class DevelopmentHelper;
}

class QSettings;
class LogFileViewer;
class StashHelper;
class CodeAssistant;
class ConverterBase64;
class DateTimeHelper;
class HtmlTableGenerator;
class CryptoHelper;
class ClipboardManager;

class DevelopmentHelper : public QMainWindow
{
  Q_OBJECT

public:
  explicit DevelopmentHelper(QWidget *parent = 0);
  ~DevelopmentHelper();

private slots:
  void on_comboBox_currentIndexChanged(int index);

private:
  void setWidgetVisible(int index);

  Ui::DevelopmentHelper *ui;
  QSettings* m_settings;

  QMap<QString, QWidget*> m_widgets;
  int m_currentIndex;
};

#endif // DEVELOPMENTHELPER_H
