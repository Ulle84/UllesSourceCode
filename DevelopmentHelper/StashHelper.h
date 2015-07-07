#ifndef STASHHELPER_H
#define STASHHELPER_H

#include <QMap>
#include <QSettings>
#include <QString>
#include <QWidget>

namespace Ui {
class StashHelper;
}

class StashHelper : public QWidget
{
  Q_OBJECT

public:
  explicit StashHelper(QWidget *parent = 0);
  ~StashHelper();

private slots:
  void on_lineEditRepository_returnPressed();
  void on_comboBoxProject_currentIndexChanged(const QString &project);
  void on_pushButtonRepositoryToClipoard_clicked();
  void on_pushButtonStashUrlToClipboard_clicked();

private:
  void setStashUrl();

  Ui::StashHelper *ui;
  QMap<QString, QString> m_projectCodes;
  QSettings* m_settings;
};

#endif // STASHHELPER_H
