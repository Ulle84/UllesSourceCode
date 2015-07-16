#ifndef PACKAGEHELPER_H
#define PACKAGEHELPER_H

#include <QMap>
#include <QString>
#include <QWidget>

class QSettings;

namespace Ui
{
class PackageHelper;
}

class PackageHelper : public QWidget
{
  Q_OBJECT

public:
  explicit PackageHelper(QWidget* parent = 0);
  ~PackageHelper();

private slots:
  void on_lineEdit_returnPressed();
  void on_pushButton_clicked();

  void on_pushButtonOpenInExplorer_clicked();

private:
  Ui::PackageHelper* ui;
  QMap<QString, QString> m_packageDirectories;
  QSettings* m_settings;
};

#endif // PACKAGEHELPER_H
