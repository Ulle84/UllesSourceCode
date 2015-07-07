#ifndef CRYPTOHELPER_H
#define CRYPTOHELPER_H

#include <QWidget>

namespace Ui {
class CryptoHelper;
}

class CryptoHelper : public QWidget
{
  Q_OBJECT

public:
  explicit CryptoHelper(QWidget *parent = 0);
  ~CryptoHelper();

private slots:
    void on_lineEditInput_returnPressed();
    void on_pushButton_clicked();

private:
  Ui::CryptoHelper *ui;
};

#endif // CRYPTOHELPER_H
