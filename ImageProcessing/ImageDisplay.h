#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include <QWidget>
#include <QGraphicsScene>
#include "Matrix.h"

// TODO decide between Matrix and Image

class Image;

namespace Ui {
class ImageDisplay;
}

class ImageDisplay : public QWidget
{
  Q_OBJECT

public:
  explicit ImageDisplay(QWidget *parent = 0);
  ~ImageDisplay();
  
  bool eventFilter(QObject *target, QEvent *event);
  void setImage(const Image* image);
  void setMatrix(const Matrix<unsigned char>* matrix);

private:
  Ui::ImageDisplay *ui;
  QGraphicsScene* m_scene;
  bool m_ctrlButtonIsPressed;
  const Image* m_image;
  const Matrix<unsigned char>* m_matrix;
};

#endif // IMAGEDISPLAY_H
