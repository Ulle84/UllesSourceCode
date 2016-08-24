#include <QDebug>
#include <QSettings>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "VisualStudioSearchResultFilter", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("basePath"))
  {
    ui->lineEditBasePath->setText(m_settings->value("basePath").toString());
  }

  if (m_settings->contains("kitType"))
  {
    ui->comboBox->setCurrentIndex(m_settings->value("kitType").toInt());
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("basePath", ui->lineEditBasePath->text());
  m_settings->setValue("kitType", ui->comboBox->currentIndex());

  delete ui;
}

void MainWindow::on_plainTextEditInput_textChanged()
{
  updateOutput();
}

void MainWindow::on_lineEditBasePath_textEdited(const QString &arg1)
{
  updateOutput();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
  updateOutput();
}

void MainWindow::updateOutput()
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

  QString sourceFolder = ui->comboBox->currentText() + "\\src\\";

  QStringList filteredFolders;
  filteredFolders << "build\\";
  filteredFolders << sourceFolder + "ACE\\";
  filteredFolders << sourceFolder + "Xerces\\";
  filteredFolders << sourceFolder + "Qwt\\";

  QStringList output;
  for (auto it = input.begin(); it != input.end(); it++)
  {
    QString tmp = it->mid(ui->lineEditBasePath->text().length());

    bool appendToOutput = true;
    for (auto it2 = filteredFolders.begin(); it2 != filteredFolders.end(); it2++)
    {
      if (tmp.startsWith(*it2))
      {
        appendToOutput = false;
        break;
      }
    }

    if (appendToOutput)
    {
      output.append(tmp);
    }
  }

  ui->plainTextEditOutput->setPlainText(output.join("\n"));

  ui->statusBar->showMessage(QString("%1 lines").arg(output.size()));
}
