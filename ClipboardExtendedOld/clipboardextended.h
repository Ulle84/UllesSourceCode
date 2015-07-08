#ifndef CLIPBOARDEXTENDED_H
#define CLIPBOARDEXTENDED_H

#include <QWidget>
class QLineEdit;
class QListView;
class QString;
class QStringList;
class QStringListModel;
class QTextEdit;

class ClipboardExtended : public QWidget
{
  Q_OBJECT

private:
  int intInsertRow;
  QLineEdit* dateTimeEdit;
  QListView* templatesListView;
  QListView* historyListView;
  QString* stringActAutoSave;
  QStringListModel* historyModel;
  QStringListModel* templatesModel;
  QStringList* historyStringList;
  QStringList* templatesStringList;
  QTextEdit* textEditClipboard;

public:
  ClipboardExtended(QWidget* parent = 0);
  ~ClipboardExtended();

private slots:
  void clipboardDataChanged();
  void clearHistory();
  void templateToClipboard();
  void historyToClipboard();
  void dateTimeToClipboard();
  void superUserPasswordToClipboard();
};

#endif // CLIPBOARDEXTENDED_H
