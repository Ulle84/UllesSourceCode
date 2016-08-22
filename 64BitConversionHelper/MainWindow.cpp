#include <QDebug>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_plainTextEditInput_textChanged()
{
  QStringList input = ui->plainTextEditInput->toPlainText().split("\n");

  if (input.length() < 3)
  {
    ui->plainTextEditOutput->setPlainText("no valid input");
    return;
  }

  input.removeFirst();
  input.removeLast();
  input.removeLast();


  QStringList output;
  for (auto it = input.begin(); it != input.end(); it++)
  {
    QString tmp = it->mid(62);

    if (!tmp.startsWith("src\\ACE")
     && !tmp.startsWith("src\\Xerces"))
    {
      output.append(tmp);
    }
  }

  ui->plainTextEditOutput->setPlainText(output.join("\n"));
  ui->plainTextEditOutput->appendPlainText(QString("%1 lines").arg(output.size()));
}
