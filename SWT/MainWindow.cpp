#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "TextEditor.h"

#include <QPushButton>
#include <QSplitter>
#include <QTreeWidget>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QSplitter* splitter = new QSplitter(Qt::Horizontal, ui->centralWidget);

  QTreeWidget* treeWidget = new QTreeWidget(splitter);
  TextEditor* textEditor = new TextEditor(splitter);

  delete textEditor;

  QListWidget* listWidget = new QListWidget(splitter);

  ui->centralWidget->layout()->addWidget(splitter);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_actionShow_Website_Preview_triggered()
{
  bool stop = true;
}
