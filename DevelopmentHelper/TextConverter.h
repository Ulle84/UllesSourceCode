#ifndef TEXTCONVERTER_H
#define TEXTCONVERTER_H

#include <QWidget>

namespace Ui
{
class TextConverter;
}

class TextConverter : public QWidget
{
  Q_OBJECT

public:
  explicit TextConverter(QWidget* parent = 0);
  ~TextConverter();

private:
  Ui::TextConverter* ui;
};

#endif // TEXTCONVERTER_H
