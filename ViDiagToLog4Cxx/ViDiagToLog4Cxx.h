#ifndef VIDIAGTOLOG4CXX_H
#define VIDIAGTOLOG4CXX_H

#include <QWidget>

namespace Ui {
class ViDiagToLog4Cxx;
}

class ViDiagToLog4Cxx : public QWidget
{
  Q_OBJECT

public:
  explicit ViDiagToLog4Cxx(QWidget *parent = 0);
  ~ViDiagToLog4Cxx();

private slots:
  void on_lineEditViDiag_editingFinished();

private:
  Ui::ViDiagToLog4Cxx* ui;
};

#endif // VIDIAGTOLOG4CXX_H
