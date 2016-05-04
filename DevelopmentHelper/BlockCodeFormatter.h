#ifndef BLOCKCODEFORMATTER_H
#define BLOCKCODEFORMATTER_H

#include <QWidget>

namespace Ui
{
class BlockCodeFormatter;
}

class BlockCodeFormatter : public QWidget
{
  Q_OBJECT

public:
  explicit BlockCodeFormatter(QWidget* parent = 0);
  ~BlockCodeFormatter();

private slots:
  void on_pushButtonBlockFormat_clicked();
  void on_pushButtonCopyToClipboard_clicked();

private:
  void convertText(QStringList& text, QList<int> lines, QStringList symbols, const QString& leadingWhitespace);

  Ui::BlockCodeFormatter* ui;

  QString m_startTag;
  QString m_seperator;
};

#endif // BLOCKCODEFORMATTER_H
