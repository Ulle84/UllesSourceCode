#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>

class QSettings;
class QRegExp;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

private slots:
  void on_pushButtonOpenFiles_clicked();
  void on_pushButtonCombineFiles_clicked();

private:
  bool readFilesAndMerge();
  void updateDir(const QString& fileName);
  bool readFile(const QString& fileName);

  Ui::MainWindow* ui;
  QStringList m_mergedFileContent;
  QSettings* m_settings;
  QDir m_dir;
  QRegExp* m_regExp;
};

#endif // MAINWINDOW_H
