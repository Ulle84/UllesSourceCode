#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>
#include "sliderspinbox.h"

namespace Ui
{
class ColorPicker;
}

class ColorPicker : public QWidget
{
  Q_OBJECT

public:
  explicit ColorPicker(QWidget* parent = 0);
  ~ColorPicker();

private slots:
  void valueChanged();
  QString createHtmlCode();
  QString createRgbCode();
  QString createHexCode();
  void changeColor();
  void RGBToClipboard();
  void updateHEXCode();
  void updateRGBCode();

  void on_pushButtonRGBCodeToClipboard_clicked();

  void on_pushButtonHEXCodeToClipboard_clicked();

private:
  Ui::ColorPicker* ui;
  SliderSpinBox* sliderSpinBoxRed;
  SliderSpinBox* sliderSpinBoxGreen;
  SliderSpinBox* sliderSpinBoxBlue;
};

#endif // COLORPICKER_H
