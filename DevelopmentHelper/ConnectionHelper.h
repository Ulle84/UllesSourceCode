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
  void on_lineEditSignal_returnPressed();
  void on_lineEditReceiver_returnPressed();
  void on_lineEditSlot_returnPressed();
  void on_checkBox_stateChanged(int arg1);

  void on_comboBox_currentIndexChanged(int index);

private:
  void createCode();

  Ui::ConnectionHelper *ui;
};

#endif // CONNECTIONHELPER_H
