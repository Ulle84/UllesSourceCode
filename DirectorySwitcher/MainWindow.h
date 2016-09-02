#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSettings;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void setWorkingDirectory(const QString& workingDirectory);

private slots:
  void on_pushButtonSelectDirectory_clicked();
  void on_pushButtonCheckDirectory_clicked();
  void on_listWidgetProjects_currentTextChanged(const QString &currentText);
  void on_pushButtonSave_clicked();
  void on_pushButtonSwitch_clicked();
  void on_pushButtonCreateNew_clicked();

private:
  void checkDirectory();
  void updateInfo();
  void showUserMessage(QString message);

  Ui::MainWindow *ui;
  QSettings* m_settings;
  QString m_currentInfoFile;
  QString m_infoFileName;
};

#endif // MAINWINDOW_H
