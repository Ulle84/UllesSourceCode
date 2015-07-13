#ifndef PACKAGEHELPER_H
#define PACKAGEHELPER_H

#include <QMap>
#include <QString>
#include <QWidget>

namespace Ui {
class PackageHelper;
}

class PackageHelper : public QWidget
{
  Q_OBJECT

public:
  explicit PackageHelper(QWidget *parent = 0);
  ~PackageHelper();

private slots:
  void on_lineEdit_returnPressed();
  void on_pushButton_clicked();

private:
  Ui::PackageHelper *ui;
  QMap<QString, QString> m_packageDirectories;
};

#endif // PACKAGEHELPER_H
