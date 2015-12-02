#include <qmath.h>

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
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
  m_ctrlButtonIsPressed(false),
  m_image(0),
  m_matrix(0)
{
  ui->setupUi(this);

  ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
  ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  ui->graphicsView->setBackgroundBrush(QBrush(QColor(Qt::gray)));
  ui->graphicsView->show();

  m_scene = new QGraphicsScene();
  ui->graphicsView->setScene(m_scene);

  ui->graphicsView->installEventFilter(this);
  ui->graphicsView->scene()->installEventFilter(this);
  ui->graphicsView->verticalScrollBar()->installEventFilter(this);
  ui->graphicsView->horizontalScrollBar()->installEventFilter(this);
}

ImageDisplay::~ImageDisplay()
{
  delete m_scene;
  delete ui;
}

bool ImageDisplay::eventFilter(QObject *target, QEvent *event)
{
  // information about pixel under cursor
  if (target == ui->graphicsView->scene())
  {
    if (event->type() == QEvent::GraphicsSceneMouseMove)
    {
      QGraphicsSceneMouseEvent* mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
      int x = mouseEvent->scenePos().rx();
      int y = mouseEvent->scenePos().ry();
      int value = 0;
      if (m_image)
      {
        value = m_image->getPixelValue(x, y);
      }

      if (m_matrix)
      {
        value = m_matrix->getValue(x, y);
      }

      ui->label->setText(QString("x: %1  y: %2  value: %3").arg(x).arg(y).arg(value));
    }
  }

  // zoom
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
  // TODO refactor doubled code - see two functions below

  m_image = image;

  QImage qImage(image->getPixels(), image->getWidth(), image->getHeight(), QImage::Format_Indexed8);
  QPixmap pixmap = QPixmap::fromImage(qImage);

  m_scene->clear();
  m_scene->addPixmap(pixmap);

  ui->graphicsView->setScene(m_scene);
}

void ImageDisplay::setMatrix(const Matrix<unsigned char>* matrix)
{
  m_matrix = matrix;

  QImage qImage(matrix->getLayer(0), matrix->getWidth(), matrix->getHeight(), QImage::Format_Indexed8);
  QPixmap pixmap = QPixmap::fromImage(qImage);

  m_scene->clear();
  m_scene->addPixmap(pixmap);

  ui->graphicsView->setScene(m_scene);
}

void ImageDisplay::setColorMatrix(const Matrix<unsigned char>* matrix)
{
  m_matrix = matrix;

  QImage qImage(matrix->getColorLayer(), matrix->getWidth(), matrix->getHeight(), QImage::Format_RGB32);
  QPixmap pixmap = QPixmap::fromImage(qImage);

  m_scene->clear();
  m_scene->addPixmap(pixmap);

  ui->graphicsView->setScene(m_scene);
}
