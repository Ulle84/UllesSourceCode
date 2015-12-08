#ifndef CONNECTIONHELPER_H
#define CONNECTIONHELPER_H

#include <QWidget>

namespace Ui {
class ConnectionHelper;
}

class ConnectionHelper : public QWidget
{
  Q_OBJECT

public:
  explicit ConnectionHelper(QWidget *parent = 0);
  ~ConnectionHelper();

private slots:
  void on_lineEditSender_returnPressed();
  void on_lineEditReceiver_returnPressed();
  void on_comboBoxReceiverType_currentIndexChanged(int index);
  void on_comboBoxSignal_currentTextChanged(const QString &arg1);
  void on_comboBoxSlot_currentTextChanged(const QString &arg1);
  void on_checkBox_stateChanged(int arg1);

private:
  void createCode();

  Ui::ConnectionHelper *ui;
};

#endif // CONNECTIONHELPER_H
