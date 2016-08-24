#include <QSettings>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "SvnUpdateFilter", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());

  delete ui;
}

void MainWindow::on_plainTextEditInput_textChanged()
{
  QStringList input = ui->plainTextEditInput->toPlainText().split('\n');

  QStringList filteredLines;
  filteredLines << "Command: Update";
  filteredLines << "Updating: ";
  filteredLines << "External: ";
  filteredLines << "Completed: ";

  QStringList output;
  for (auto it = input.begin(); it != input.end(); ++it)
  {
    bool appendLine = true;
    for (auto it2 = filteredLines.begin(); it2 != filteredLines.end(); ++it2)
    {
      if (it->startsWith(*it2))
      {
        appendLine = false;
        break;
      }
    }

    if (appendLine)
    {
      output.append(*it);
    }
  }

  ui->plainTextEditOutput->setPlainText(output.join('\n'));
}
