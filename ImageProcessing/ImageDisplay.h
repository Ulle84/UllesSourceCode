#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include <QWidget>
#include <QGraphicsScene>

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

private:
  Ui::ImageDisplay *ui;
  QGraphicsScene* m_scene;
  bool m_ctrlButtonIsPressed;
  const Image* m_image;
};

#endif // IMAGEDISPLAY_H
