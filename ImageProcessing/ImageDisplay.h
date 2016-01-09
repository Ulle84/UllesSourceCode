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
  void setImage(Image* image);

private slots:
  void on_pushButtonZoomIn_clicked();

  void on_pushButtonZoomOut_clicked();

  void on_pushButton_clicked();

private:
  Ui::ImageDisplay *ui;
  QGraphicsScene* m_scene;
  bool m_ctrlButtonIsPressed;
  Image* m_image;

  int m_mouseX;
  int m_mouseY;
  bool m_displayLine;

  int m_lineStartX;
  int m_lineStartY;

  int m_lineEndX;
  int m_lineEndY;
};

#endif // IMAGEDISPLAY_H
