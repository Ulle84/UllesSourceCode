#ifndef CLIPBOARDEXTENDED_H
#define CLIPBOARDEXTENDED_H

#include <QWidget>

namespace Ui {
class ClipboardExtended;
}

class ClipboardExtended : public QWidget
{
  Q_OBJECT
  
public:
  explicit ClipboardExtended(QWidget *parent = 0);
  ~ClipboardExtended();
  
private:
  Ui::ClipboardExtended *ui;
};

#endif // CLIPBOARDEXTENDED_H
