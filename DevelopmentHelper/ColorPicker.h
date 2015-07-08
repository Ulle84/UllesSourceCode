#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QWidget>

#include "SliderSpinBox.h"

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
  void on_pushButtonRGBCodeToClipboard_clicked();
  void on_pushButtonHEXCodeToClipboard_clicked();

private:
  QString createHtmlCode();
  QString createRgbCode();
  QString createHexCode();
  void changeColor();
  void RGBToClipboard();
  void updateHEXCode();
  void updateRGBCode();

  Ui::ColorPicker* ui;
  SliderSpinBox* sliderSpinBoxRed;
  SliderSpinBox* sliderSpinBoxGreen;
  SliderSpinBox* sliderSpinBoxBlue;
};

#endif // COLORPICKER_H
