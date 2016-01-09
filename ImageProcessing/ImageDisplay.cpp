#include <qmath.h>

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QImage>
#include <QPixmap>
#include <QScrollBar>
#include <QWheelEvent>
#include <QClipboard>

#include "Image.h"

#include "ImageDisplay.h"
#include "ui_ImageDisplay.h"

ImageDisplay::ImageDisplay(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ImageDisplay),
  m_ctrlButtonIsPressed(false),
  m_image(0),
  m_displayLine(false)
{
  ui->setupUi(this);

  ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  //ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
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
  if (target == ui->graphicsView->scene())
  {
    if (event->type() == QEvent::GraphicsSceneMouseMove)
    {
      // information about pixel under cursor
      QGraphicsSceneMouseEvent* mouseEvent = static_cast<QGraphicsSceneMouseEvent*>(event);
      m_mouseX = mouseEvent->scenePos().rx();
      m_mouseY = mouseEvent->scenePos().ry();

      QString pixelInformation;

      if (m_image)
      {
        unsigned int qtyLayers = m_image->getQtyLayers();

        if (qtyLayers == 1)
        {
          pixelInformation = tr("gray value: %1").arg(m_image->getValue(m_mouseX, m_mouseY));
        }
        else if (qtyLayers == 3 || qtyLayers == 4)
        {
          pixelInformation = tr("red: %1  green: %2  blue: %3").arg(m_image->getValue(m_mouseX, m_mouseY, 0)).arg(m_image->getValue(m_mouseX, m_mouseY, 1)).arg(m_image->getValue(m_mouseX, m_mouseY, 2));

          if (qtyLayers == 4)
          {
            pixelInformation.append(tr("  alpha: %1").arg(m_image->getValue(m_mouseX, m_mouseY, 3)));
          }
        }
      }
      ui->label->setText(QString("x: %1  y: %2  %3").arg(m_mouseX).arg(m_mouseY).arg(pixelInformation));
    }
    else if (event->type() == QEvent::GraphicsSceneMousePress)
    {
      m_displayLine = true;
      m_lineStartX = m_mouseX;
      m_lineStartY = m_mouseY;
    }
    else if (event->type() == QEvent::GraphicsSceneMouseRelease)
    {
      m_displayLine = true;
      m_lineEndX = m_mouseX;
      m_lineEndY = m_mouseY;

      ui->lineEdit->setText(QString("Line line(Point(%1, %2), Point(%3, %4));").arg(m_lineStartX).arg(m_lineStartY).arg(m_lineEndX).arg(m_lineEndY));
      ui->lineEditInformation->setText(QString("dx: %1   dy: %2").arg(m_lineEndX - m_lineStartX).arg(m_lineEndY - m_lineStartY));
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

void ImageDisplay::setImage(Image* image)
{
  m_image = image;

  const unsigned char* data = m_image->getLayer(0);
  QImage::Format format = QImage::Format_Indexed8;

  if (image->getQtyLayers() == 3)
  {
    std::vector<unsigned int> layerIndices;
    layerIndices.push_back(2);
    layerIndices.push_back(1);
    layerIndices.push_back(0);
    layerIndices.push_back(0);
    data = m_image->getSingleLayer(layerIndices);
    format = QImage::Format_RGB32;
  }

  if (image->getQtyLayers() == 4)
  {
    std::vector<unsigned int> layerIndices;
    layerIndices.push_back(2);
    layerIndices.push_back(1);
    layerIndices.push_back(0);
    layerIndices.push_back(3);
    data = m_image->getSingleLayer(layerIndices);
    format = QImage::Format_ARGB32;
  }

  QImage qImage(data, image->getWidth(), image->getHeight(), format);
  QPixmap pixmap = QPixmap::fromImage(qImage);

  m_scene->clear();
  m_scene->addPixmap(pixmap);

  ui->graphicsView->setScene(m_scene);

  //ui->graphicsView->fitInView( m_scene->sceneRect(), Qt::KeepAspectRatio );
}

void ImageDisplay::on_pushButtonZoomIn_clicked()
{
  ui->graphicsView->scale(1.25, 1.25);
}

void ImageDisplay::on_pushButtonZoomOut_clicked()
{
  ui->graphicsView->scale(0.8, 0.8);
}

void ImageDisplay::on_pushButton_clicked()
{
  QApplication::clipboard()->setText(ui->lineEdit->text());
}
