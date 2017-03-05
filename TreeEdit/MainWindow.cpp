#include <QSettings>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->treeEdit->setTree(readFile());

  m_settings = new QSettings("Ulle", "TreeEdit", this);

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }
  if (m_settings->contains("headerState"))
  {
    ui->treeEdit->setHeaderState(m_settings->value("headerState").toByteArray());
  }



  connect(ui->treeEdit, &TreeEdit::idChanged, this, &MainWindow::onTreeEditIdChanged);

  //ui->treeEdit->setMaxIndentation(2);
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("headerState", ui->treeEdit->headerState());
  writeFile();
  delete ui;
}

void MainWindow::on_actionAddNewNode_triggered()
{
  ui->treeEdit->addNode();
}

void MainWindow::on_actionAddNewChildNode_triggered()
{
  ui->treeEdit->addChildNode();
}

void MainWindow::on_actionRemoveNode_triggered()
{
  ui->treeEdit->removeNode();
}

void MainWindow::on_actionMoveUp_triggered()
{
  ui->treeEdit->moveUp();
}

void MainWindow::on_actionMoveDown_triggered()
{
  ui->treeEdit->moveDown();
}

void MainWindow::on_actionMoveLeft_triggered()
{
  ui->treeEdit->moveLeft();
}

void MainWindow::on_actionMoveRight_triggered()
{
  ui->treeEdit->moveRight();
}

void MainWindow::on_actionInsertColunn_triggered()
{
  ui->treeEdit->insertColumn();
}

void MainWindow::on_actionRemoveColumn_triggered()
{
  ui->treeEdit->removeColumn();
}

void MainWindow::onTreeEditIdChanged(int id)
{
  //qDebug() << "onTreeEditIdChanged id:" << id;

  if (m_currentId >= 0)
  {
    m_testContent[m_currentId] = ui->plainTextEdit->toPlainText();
  }

  m_currentId = id;
  ui->plainTextEdit->setPlainText(m_testContent[m_currentId]);

}

QJsonObject MainWindow::readFile()
{
  QFile file(m_fileName);

  if (!file.open(QIODevice::ReadOnly))
  {
    qWarning("Couldn't open save file.");
  }

  QString settings = file.readAll();
  file.close();

  QJsonDocument sd = QJsonDocument::fromJson(settings.toUtf8());
  return sd.object();
}

void MainWindow::writeFile()
{
  QFile file(m_fileName);

  if (!file.open(QIODevice::WriteOnly))
  {
    qWarning("Couldn't open save file.");
  }

  QJsonDocument jsonDocument(ui->treeEdit->toJson());

  file.write(jsonDocument.toJson());
  file.close();
}
