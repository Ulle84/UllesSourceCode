#ifndef DOUBLEBUTTON_H
#define DOUBLEBUTTON_H

#include <QWidget>
#include <QStringList>
#include <QVariantMap>

namespace Ui
{
class DoubleButton;
}

class DoubleButton : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QString buttonText1 READ buttonText1 WRITE setButtonText1)
  Q_PROPERTY(QStringList buttonTexts READ buttonTexts WRITE setButtonTexts)
  Q_PROPERTY(QVariantMap variantMap READ variantMap WRITE setVariantMap)

public:
  explicit DoubleButton(QWidget* parent = 0);
  ~DoubleButton();

  QString buttonText1();
  QString buttonText2();
  QStringList buttonTexts();
  QVariantMap variantMap();

  void setButtonText1(const QString& buttonText1);
  void setButtonText2(const QString& buttonText2);
  void setButtonTexts(const QStringList& buttonTexts);
  void setVariantMap(const QVariantMap& variantMap);

private slots:
  void on_pushButton1_clicked();
  void on_pushButton2_clicked();

private:
  Ui::DoubleButton* ui;
  QStringList m_test;
  QVariantMap m_variantMap;
};

#endif // DOUBLEBUTTON_H
