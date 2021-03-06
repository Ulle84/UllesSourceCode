#include <QtAlgorithms>
#include <QSettings>

#include "MainWindow.h"
#include "ui_MainWindow.h"

bool compareOutputStrings(const QString& s1, const QString& s2)
{
  // 2>------ Erstellen gestartet: Projekt: EISMatrixSimulator_automoc,
  // parse number before '>'-sign and compare

  return s1.left(s1.indexOf('>')).toInt() < s2.left(s2.indexOf('>')).toInt();
}

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  /*m_settings = new QSettings("Ulle", "VisualStudioOutputSorter", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }*/
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  delete ui;
}

void MainWindow::sortLines()
{
  qStableSort(m_textLines.begin(), m_textLines.end(), compareOutputStrings);
}

void MainWindow::on_plainTextEditSource_textChanged()
{
  m_textLines = ui->plainTextEditSource->toPlainText().split("\n");

  sortLines();

  ui->plainTextEditDestination->setPlainText(m_textLines.join("\n"));
}
