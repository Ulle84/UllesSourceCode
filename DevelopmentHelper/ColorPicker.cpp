#include "ColorPicker.h"
#include "ui_ColorPicker.h"

#include <QClipboard>

ColorPicker::ColorPicker(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::ColorPicker)
{
  ui->setupUi(this);

  int minimum = 0;
  int maximum = 255;

  sliderSpinBoxRed = new SliderSpinBox();
  sliderSpinBoxGreen = new SliderSpinBox();
  sliderSpinBoxBlue = new SliderSpinBox();

  sliderSpinBoxRed->setText(tr("Red"));
  sliderSpinBoxGreen->setText(tr("Green"));
  sliderSpinBoxBlue->setText(tr("Blue"));

  sliderSpinBoxRed->setMinimum(minimum);
  sliderSpinBoxRed->setMaximum(maximum);
  sliderSpinBoxGreen->setMinimum(minimum);
  sliderSpinBoxGreen->setMaximum(maximum);
  sliderSpinBoxBlue->setMinimum(minimum);
  sliderSpinBoxBlue->setMaximum(maximum);


  ui->verticalLayout->addWidget(sliderSpinBoxRed);
  ui->verticalLayout->addWidget(sliderSpinBoxGreen);
  ui->verticalLayout->addWidget(sliderSpinBoxBlue);

  connect(sliderSpinBoxRed, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));
  connect(sliderSpinBoxGreen, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));
  connect(sliderSpinBoxBlue, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));

  valueChanged();
}

ColorPicker::~ColorPicker()
{
  delete ui;
}

void ColorPicker::valueChanged()
{
  changeColor();
  updateRGBCode();
  updateHEXCode();
}

void ColorPicker::changeColor()
{
  ui->textEdit->setHtml(createHtmlCode());
}

void ColorPicker::RGBToClipboard()
{
  QApplication::clipboard()->setText(createRgbCode());
}

void ColorPicker::updateHEXCode()
{
  ui->lineEditHEXCode->setText(createHexCode());
}

void ColorPicker::updateRGBCode()
{
  ui->lineEditRGBCode->setText(createRgbCode());
}

QString ColorPicker::createHtmlCode()
{
  QString string = "<html><body style=\"background-color: ";
  string.append(createRgbCode());
  string.append("\"></body></html>");
  return string;
}

QString ColorPicker::createRgbCode()
{
  QString string = "rgb(" + QVariant(sliderSpinBoxRed->value()).toString() + ", " +  QVariant(sliderSpinBoxGreen->value()).toString() + ", " + QVariant(sliderSpinBoxBlue->value()).toString() + ")";
  return string;
}

QString ColorPicker::createHexCode()
{
  return QString("#%1%2%3").arg(sliderSpinBoxRed->value(), 2, 16, QChar('0')).arg(sliderSpinBoxGreen->value(), 2, 16, QChar('0')).arg(sliderSpinBoxBlue->value(), 2, 16, QChar('0'));
}

void ColorPicker::on_pushButtonRGBCodeToClipboard_clicked()
{
  QApplication::clipboard()->setText(ui->lineEditRGBCode->text());
}

void ColorPicker::on_pushButtonHEXCodeToClipboard_clicked()
{
  QApplication::clipboard()->setText(ui->lineEditHEXCode->text());
}
