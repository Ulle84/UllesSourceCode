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
#include "GeometryCodeGenerator.h"

#include "ImageDisplay.h"
#include "ui_ImageDisplay.h"

ImageDisplay::ImageDisplay(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ImageDisplay),
  m_ctrlButtonIsPressed(false),
  m_image(0),
  m_techingActive(false),
  m_movingActive(false),
  m_pen(QPen(QColor(255, 0, 0))),
  m_brush(QBrush(Qt::DiagCrossPattern))
{
  ui->setupUi(this);

  ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
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
    QGraphicsSceneMouseEvent* mouseEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);

    bool teachButtonChecked = ui->toolButtonTeachLine->isChecked() || ui->toolButtonTeachRectangle->isChecked() || ui->toolButtonTeachCircle->isChecked();

    if (event->type() == QEvent::GraphicsSceneMouseMove)
    {
      if (mouseEvent)
      {
        m_mouseMovePosition = mouseEvent->scenePos();
      }

      int x = qRound(m_mouseMovePosition.x());
      int y = qRound(m_mouseMovePosition.y());

      QString pixelInformation;

      if (m_image)
      {
        unsigned int qtyLayers = m_image->getQtyLayers();

        if (qtyLayers == 1)
        {
          pixelInformation = tr("gray value: %1").arg(m_image->getValue(x, y));
        }
        else if (qtyLayers == 3 || qtyLayers == 4)
        {
          pixelInformation = tr("red: %1  green: %2  blue: %3").arg(m_image->getValue(x, y, 0)).arg(m_image->getValue(x, y, 1)).arg(m_image->getValue(x, y, 2));

          if (qtyLayers == 4)
          {
            pixelInformation.append(tr("  alpha: %1").arg(m_image->getValue(x, y, 3)));
          }
        }
      }

      ui->label->setText(QString("x: %1  y: %2  %3").arg(x).arg(y).arg(pixelInformation));

      if (m_techingActive)
      {
        if (ui->toolButtonTeachLine->isChecked())
        {
          QLineF line (m_mousePressPosition, m_mouseMovePosition);

          m_currentTeachingLine->setLine(line);
          ui->lineEditCode->setText(GeometryCodeGenerator::generate(line));
        }
        else if (ui->toolButtonTeachRectangle->isChecked())
        {
          QRectF rect (m_mousePressPosition, m_mouseMovePosition);

          m_currentTeachingRect->setRect(rect);
          ui->lineEditCode->setText(GeometryCodeGenerator::generate(rect));
        }
        else if (ui->toolButtonTeachCircle->isChecked())
        {
          QPointF delta = m_mouseMovePosition - m_mousePressPosition;

          double r = sqrt(delta.x() * delta.x() + delta.y() * delta.y());

          QPointF p1(m_mousePressPosition.x() - r, m_mousePressPosition.y() - r);
          QPointF p2(m_mousePressPosition.x() + r, m_mousePressPosition.y() + r);
          QRectF rect = QRectF(p1, p2);

          m_currentTeachingEllipse->setRect(QRectF(p1, p2));
          ui->lineEditCode->setText(GeometryCodeGenerator::generate(rect, true, true));
        }
      }
      else if (m_movingActive)
      {
        if (mouseEvent)
        {
          QPointF lastPos = mouseEvent->lastScenePos();
          QPointF delta = mouseEvent->lastScenePos() - mouseEvent->scenePos();
          QRectF rect = m_currentTeachingRect->rect();
          rect.moveTo(rect.topLeft() - delta);
          m_currentTeachingRect->setRect(rect);
        }
      }
    }
    else if (event->type() == QEvent::GraphicsSceneMousePress)
    {
      if (mouseEvent)
      {
        m_mousePressPosition = mouseEvent->scenePos();
      }

      if (teachButtonChecked)
      {
        m_techingActive = true;

        if (ui->toolButtonTeachLine->isChecked())
        {
          m_currentTeachingLine = m_scene->addLine(QLineF(m_mousePressPosition, m_mousePressPosition), m_pen);
        }
        else if (ui->toolButtonTeachRectangle->isChecked())
        {
          m_currentTeachingRect = m_scene->addRect(QRectF(m_mousePressPosition, m_mousePressPosition), m_pen, m_brush);
        }
        else if (ui->toolButtonTeachCircle->isChecked())
        {
          m_currentTeachingEllipse = m_scene->addEllipse(QRectF(m_mousePressPosition, m_mousePressPosition), m_pen, m_brush);
        }
      }
      else if (!ui->toolButtonDragImage->isChecked())
      {
        QGraphicsItem* item = m_scene->itemAt(m_mouseMovePosition, ui->graphicsView->transform());

        if (item->type() == QGraphicsLineItem::Type)
        {
          QGraphicsLineItem* lineItem = dynamic_cast<QGraphicsLineItem*>(item);

          if (lineItem)
          {
            ui->lineEditCode->setText(GeometryCodeGenerator::generate(lineItem->line()));
          }
        }
        else if (item->type() == QGraphicsRectItem::Type)
        {
          QGraphicsRectItem* rectItem = dynamic_cast<QGraphicsRectItem*>(item);

          if (rectItem)
          {
            m_movingActive = true;
            m_currentTeachingRect = rectItem;
            ui->lineEditCode->setText(GeometryCodeGenerator::generate(rectItem->rect()));
          }
        }
        else if (item->type() == QGraphicsEllipseItem::Type)
        {
          QGraphicsEllipseItem* ellipseItem = dynamic_cast<QGraphicsEllipseItem*>(item);

          if (ellipseItem)
          {
            ui->lineEditCode->setText(GeometryCodeGenerator::generate(ellipseItem->rect(), true, true));
          }
        }
        else
        {
          ui->lineEditCode->clear();
        }
      }
    }
    else if (event->type() == QEvent::GraphicsSceneMouseRelease)
    {
      m_techingActive = false;
      m_movingActive = false;
      /*if (teachButtonChecked)
      {
        m_techingActive = false;
      }

      if (m_movingActive)
      {
        m_movingActive = false;
      }*/
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

void ImageDisplay::on_pushButtonClipboard_clicked()
{
  QApplication::clipboard()->setText(ui->lineEditCode->text());
}

void ImageDisplay::on_toolButtonDragImage_clicked(bool checked)
{
  if (checked)
  {
    ui->toolButtonTeachLine->setChecked(false);
    ui->toolButtonTeachRectangle->setChecked(false);
    ui->toolButtonTeachCircle->setChecked(false);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
  }
}

void ImageDisplay::on_toolButtonTeachLine_clicked(bool checked)
{
  if (checked)
  {
    ui->toolButtonDragImage->setChecked(false);
    ui->toolButtonTeachRectangle->setChecked(false);
    ui->toolButtonTeachCircle->setChecked(false);
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
  }
}

void ImageDisplay::on_toolButtonTeachRectangle_clicked(bool checked)
{
  if (checked)
  {
    ui->toolButtonDragImage->setChecked(false);
    ui->toolButtonTeachLine->setChecked(false);
    ui->toolButtonTeachCircle->setChecked(false);
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
  }
}

void ImageDisplay::on_toolButtonTeachCircle_clicked(bool checked)
{
  if (checked)
  {
    ui->toolButtonDragImage->setChecked(false);
    ui->toolButtonTeachLine->setChecked(false);
    ui->toolButtonTeachRectangle->setChecked(false);
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
  }
}
