#ifndef NUMBERCONVERTER_H
#define NUMBERCONVERTER_H

#include <QWidget>
#include <QList>
#include <QPair>
#include <QLineEdit>

namespace Ui
{
class NumberConverter;
}

class NumberConverter : public QWidget
{
  Q_OBJECT

public:
  explicit NumberConverter(QWidget* parent = 0);
  ~NumberConverter();

private slots:
  void on_lineEditDec_returnPressed();
  void on_lineEditHex_returnPressed();
  void on_lineEditOct_returnPressed();
  void on_lineEditBin_returnPressed();

private:
  Ui::NumberConverter* ui;
  void updateWidgets(QLineEdit* source, int base);
};

#endif // NUMBERCONVERTER_H
