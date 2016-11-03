#include <QFileDialog>
#include <QSettings>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "IncludeFinder", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("selectedDirectory"))
  {
    ui->lineEdit->setText(m_settings->value("selectedDirectory").toString());
  }
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("selectedDirectory", ui->lineEdit->text());

  delete ui;
}

void MainWindow::on_pushButtonSelectDirectory_clicked()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("select folder"), ui->lineEdit->text());

  if (!directory.isEmpty())
  {
    ui->lineEdit->setText(directory);
  }
}

void MainWindow::on_pushButtonSearch_clicked()
{
  QStringList includes = ui->plainTextEditIncludes->toPlainText().split('\n', QString::SkipEmptyParts);

  ui->plainTextEditOuput->setPlainText(m_includeFinder.files(ui->lineEdit->text(), includes).join('\n'));
}
