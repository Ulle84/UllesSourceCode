#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QString>

class QSettings;

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_comboBoxType_currentIndexChanged(const QString& type);
  void on_comboBoxSignal_currentIndexChanged(const QString &signal);
  void on_lineEditControlName_textChanged(const QString &controlName);

  void on_pushButtonCopyToClipboard_clicked();

private:
  void update();
  void readFile();

  Ui::MainWindow *ui;

  QSettings* m_settings;
};

#endif // MAINWINDOW_H
