#include "mainwindow.h"
#include <QtGui>

/* General Idea
Ein Mini-Programm, dass einen Dialog mit dem aktuellen Datum und der aktuellen KW anzeigt

Verschiedene Datenformate werden angezeigt und können mit einem Klick in die Zwischenablage übernommen werden
*/

// Bugs

// ToDos

// Enhancements
// TimeExtension

// Ideas
// Andere Strukur, anstatt button01 ... und createClipboard...01..
// kann man ein Array von Funktionen machen?

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
  calendar = new QCalendarWidget();
  calendar->setFirstDayOfWeek(Qt::Monday);
  //calendar->setGridVisible(true);
  QPushButton* todayButton = new QPushButton("Today");
  QPushButton* button01 = new QPushButton("yyyy-MM-dd");
  QPushButton* button02 = new QPushButton("dd.MM.yyyy");

  QVBoxLayout* mainLayout = new QVBoxLayout();
  mainLayout->addWidget(calendar);
  mainLayout->addWidget(todayButton);
  mainLayout->addWidget(button01);
  mainLayout->addWidget(button02);
  QWidget* centralWidget = new QWidget();
  centralWidget->setLayout(mainLayout);
  setCentralWidget(centralWidget);

  // connect signals and slots
  connect(button01, SIGNAL(clicked()), this, SLOT(createClipboardContent01()));
  connect(button02, SIGNAL(clicked()), this, SLOT(createClipboardContent02()));
  connect(todayButton, SIGNAL(clicked()), this, SLOT(goToToday()));
}

MainWindow::~MainWindow()
{

}

bool MainWindow::createClipboardContent01()
{
  QApplication::clipboard()->setText(calendar->selectedDate().toString("yyyy-MM-dd"));
  return true;
}

bool MainWindow::createClipboardContent02()
{
  QApplication::clipboard()->setText(calendar->selectedDate().toString("dd.MM.yyyy"));
  return true;
}

bool MainWindow::goToToday()
{
  calendar->setSelectedDate(QDate::currentDate());
  return true;
}
