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
  int m_eventCounter;
  bool m_ctrlButtonIsPressed;
};

#endif // IMAGEDISPLAY_H
