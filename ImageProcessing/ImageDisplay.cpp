#include <qmath.h>

#include <QDebug>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>
#include <QScrollBar>
#include <QWheelEvent>

#include "ImageDisplay.h"
#include "ui_ImageDisplay.h"

#include "Image.h"

ImageDisplay::ImageDisplay(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ImageDisplay),
  m_eventCounter(0),
  m_ctrlButtonIsPressed(false)
{
  ui->setupUi(this);

  ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
  ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  ui->graphicsView->setBackgroundBrush(QBrush(QColor(Qt::gray)));
  ui->graphicsView->show();

  ui->graphicsView->installEventFilter(this);
  ui->graphicsView->verticalScrollBar()->installEventFilter(this);
  ui->graphicsView->horizontalScrollBar()->installEventFilter(this);

  m_scene = new QGraphicsScene();
}

ImageDisplay::~ImageDisplay()
{
  delete m_scene;
  delete ui;
}

bool ImageDisplay::eventFilter(QObject *target, QEvent *event)
{
  if (target == ui->graphicsView || target == ui->graphicsView->verticalScrollBar() || target == ui->graphicsView->horizontalScrollBar())
  {    
    if (event->type() == QEvent::KeyPress)
    {
      QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

      if (keyEvent->key() == Qt::Key_Control)
      {
        m_ctrlButtonIsPressed = true;
      }
    }
    else if (event->type() == QEvent::KeyRelease)
    {
      QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

      if (keyEvent->key() == Qt::Key_Control)
      {
        m_ctrlButtonIsPressed = false;
      }
    }
    else if (event->type() == QEvent::Wheel && m_ctrlButtonIsPressed)
    {
      QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);

      qreal factor = qPow(1.2, wheelEvent->delta() / 240.0);
      ui->graphicsView->scale(factor, factor);
      return true;
    }
  }
  return QWidget::eventFilter(target, event);
}

void ImageDisplay::setImage(const Image* image)
{
  QImage qImage(image->getPixels(), image->getWidth(), image->getHeight(), QImage::Format_Indexed8);
  QPixmap pixmap = QPixmap::fromImage(qImage);

  m_scene->addPixmap(pixmap);

  ui->graphicsView->setScene(m_scene);
}
