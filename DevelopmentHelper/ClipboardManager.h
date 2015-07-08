#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include <QWidget>

namespace Ui {
class ClipboardManager;
}

class ClipboardManager : public QWidget
{
  Q_OBJECT

public:
  explicit ClipboardManager(QWidget *parent = 0);
  ~ClipboardManager();

private:
  Ui::ClipboardManager *ui;
};

#endif // CLIPBOARDMANAGER_H
