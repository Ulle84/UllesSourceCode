#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include <QString>
#include <QStringList>
#include <QWidget>

namespace Ui
{
class ClipboardManager;
}

class QStringListModel;

class ClipboardManager : public QWidget
{
  Q_OBJECT

public:
  explicit ClipboardManager(QWidget* parent = 0);
  ~ClipboardManager();

private slots:
  void clipboardDataChanged();
  void historyToClipboard();
  void on_pushButtonClearHistory_clicked();
  void on_pushButtonClearClipboard_clicked();
  void on_checkBox_stateChanged(int state);

private:
  void update();

  Ui::ClipboardManager* ui;

  QString m_currentClipbardData;
  QString m_lastClipbardData;
  QStringList m_clipbardHistory;
  QStringListModel* m_stringListModel;
};

#endif // CLIPBOARDMANAGER_H
