#ifndef BITBUCKETHELPER_H
#define BITBUCKETHELPER_H

#include <QMap>
#include <QSettings>
#include <QString>
#include <QWidget>

namespace Ui
{
class BitbucketHelper;
}

class BitbucketHelper : public QWidget
{
  Q_OBJECT

public:
  explicit BitbucketHelper(QWidget* parent = 0);
  ~BitbucketHelper();

private slots:
  void on_lineEditRepository_returnPressed();
  void on_comboBoxProject_currentIndexChanged(const QString& project);
  void on_pushButtonRepositoryToClipoard_clicked();
  void on_pushButtonStashUrlToClipboard_clicked();

private:
  void setStashUrl();

private:
  Ui::BitbucketHelper* ui;
  QMap<QString, QString> m_projectCodes;
  QSettings* m_settings;
};

#endif // BITBUCKETHELPER_H
