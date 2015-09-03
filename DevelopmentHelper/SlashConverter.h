#ifndef SLASHCONVERTER_H
#define SLASHCONVERTER_H

#include <QWidget>

namespace Ui
{
class SlashConverter;
}

class SlashConverter : public QWidget
{
  Q_OBJECT

public:
  explicit SlashConverter(QWidget* parent = 0);
  ~SlashConverter();

private slots:
  void on_pushButtonConvertToBackslash_clicked();
  void on_pushButtonConvertToFowardSlash_clicked();

private:
  void updateText(const QString& text);

  Ui::SlashConverter* ui;
};

#endif // SLASHCONVERTER_H
