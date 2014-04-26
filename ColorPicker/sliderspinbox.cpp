#include "sliderspinbox.h"
#include "ui_sliderspinbox.h"

SliderSpinBox::SliderSpinBox(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::SliderSpinBox)
{
  ui->setupUi(this);

  connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), ui->spinBox, SLOT(setValue(int)));
  connect(ui->spinBox, SIGNAL(valueChanged(int)), ui->horizontalSlider, SLOT(setValue(int)));
  connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
}

SliderSpinBox::~SliderSpinBox()
{
  delete ui;
}

int SliderSpinBox::value()
{
  return ui->spinBox->value();
}

void SliderSpinBox::setValue(int value)
{
  ui->spinBox->setValue(value);
}

void SliderSpinBox::setMaximum(int maximum)
{
  ui->horizontalSlider->setMaximum(maximum);
  ui->spinBox->setMaximum(maximum);
}

void SliderSpinBox::setMinimum(int minimum)
{
  ui->horizontalSlider->setMinimum(minimum);
  ui->spinBox->setMinimum(minimum);
}

void SliderSpinBox::setText(QString text)
{
  ui->label->setText(text);
}
