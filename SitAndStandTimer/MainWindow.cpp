#include <QSettings>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "SitAndStandTimer");

  if (m_settings->contains("geometry"))
  {
    setGeometry(m_settings->value("geometry").toRect());
  }

  if (m_settings->contains("standTime"))
  {
    ui->spinBoxStandTime->setValue(m_settings->value("standTime").toInt());
  }

  if (m_settings->contains("sitTime"))
  {
    ui->spinBoxSitTime->setValue(m_settings->value("sitTime").toInt());
  }

  m_position = Undefined;

  m_timer = new QTimer(this);
  m_timer->start(1000);
  connect(m_timer, &QTimer::timeout, this, &MainWindow::update);
}

MainWindow::~MainWindow()
{
  m_settings->setValue("geometry", geometry());
  m_settings->setValue("standTime", ui->spinBoxStandTime->value());
  m_settings->setValue("sitTime", ui->spinBoxSitTime->value());

  delete ui;
}

void MainWindow::update()
{
  if (m_position != Undefined)
  {
    quint64 secondsDiff = QDateTime::currentDateTime().secsTo(m_dateTimePositionChange);

    if (secondsDiff > 0)
    {
      QString message = tr("Remaining ");

      if (m_position == Sitting)
      {
        message.append(tr("sitting"));
      }
      else if (m_position == Standing)
      {
        message.append(tr("standing"));
      }

      message.append(tr(" time: "));
      message.append(timeToString(secondsDiff / 60, secondsDiff % 60));

      ui->statusBar->showMessage(message);
    }
    else
    {
      ui->statusBar->clearMessage();
      if (m_position == Sitting)
      {
        m_position = Undefined;
        QMessageBox messageBox;
        messageBox.setText(tr("sitting time is over"));
        //messageBox.raise();
        messageBox.exec();
      }
      else if (m_position == Standing)
      {
        m_position = Undefined;
        QMessageBox messageBox;
        messageBox.setText(tr("standing time is over"));
        //messageBox.raise();
        messageBox.exec();
      }
    }
  }
  else
  {
     ui->statusBar->clearMessage();
  }
}

void MainWindow::on_pushButtonStartSitting_clicked()
{
  m_position = Sitting;
  m_dateTimePositionChange = QDateTime::currentDateTime().addSecs(ui->spinBoxSitTime->value() * 60);
  update();
}

void MainWindow::on_pushButtonStartStanding_clicked()
{
  m_position = Standing;
  m_dateTimePositionChange = QDateTime::currentDateTime().addSecs(ui->spinBoxStandTime->value() * 60);
  update();
}

QString MainWindow::timeToString(int minutes, int seconds)
{
  QString time;

  if (minutes < 10)
  {
    time.append("0");
  }
  time.append(QString("%1:").arg(minutes));

  if (seconds < 10)
  {
    time.append("0");
  }
  time.append(QString("%1").arg(seconds));

  return time;
}
