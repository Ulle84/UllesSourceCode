#ifndef CONVERTERBASE64_H
#define CONVERTERBASE64_H

#include <QWidget>

namespace Ui {
class ConverterBase64;
}

class ConverterBase64 : public QWidget
{
  Q_OBJECT

public:
  explicit ConverterBase64(QWidget *parent = 0);
  ~ConverterBase64();

private slots:
  void on_lineEditPlainText_editingFinished();
  void on_lineEditBase64EncodedText_editingFinished();

private:
  Ui::ConverterBase64 *ui;
};

#endif // CONVERTERBASE64_H
