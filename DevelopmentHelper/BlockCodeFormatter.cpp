#include <QClipboard>
#include <QDebug>

#include "BlockCodeFormatter.h"
#include "ui_BlockCodeFormatter.h"

// TODO detect block comment /* ... */

BlockCodeFormatter::BlockCodeFormatter(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::BlockCodeFormatter)
{
  ui->setupUi(this);
}

BlockCodeFormatter::~BlockCodeFormatter()
{
  delete ui;
}

void BlockCodeFormatter::on_pushButtonBlockFormat_clicked()
{
  ui->plainTextEditOutput->clear();

  QStringList lines = ui->plainTextEditInput->toPlainText().split("\n");
  QStringList symbols;
  QList<int> linesToConvert;

  QString startTag = "//|";

  QString leadingWhitespace;
  bool convertNextLine = false;

  for (int i = 0; i < lines.length(); i++)
  {
    QString trimmedLine = lines.at(i).trimmed();

    if (trimmedLine.startsWith(startTag))
    {
      qDebug() << "found start tag in line" << i;
      leadingWhitespace = lines.at(i).left(lines.at(i).indexOf(startTag));
      convertNextLine = true;
      symbols = trimmedLine.mid(startTag.length()).split("|");
      symbols.removeLast();
      qDebug() << "symbols:" << symbols;
    }
    else if (trimmedLine.startsWith("//"))
    {
      // it seems to be a comment -> do nothing
      qDebug() << "skipping comment in line" << i;
    }
    else if (trimmedLine.isEmpty())
    {
      qDebug() << "found block seperator in line" << i;
      convertText(lines, linesToConvert, symbols, leadingWhitespace);
      linesToConvert.clear();
      convertNextLine = false;
    }
    else
    {
      if (convertNextLine)
      {
        linesToConvert.append(i);
      }

      if (i == lines.length() - 1)
      {
        qDebug() << "reached end in line" << i;
        convertText(lines, linesToConvert, symbols, leadingWhitespace);
      }
    }
  }

  ui->plainTextEditOutput->appendPlainText(lines.join("\n"));
}

void BlockCodeFormatter::on_pushButtonCopyToClipboard_clicked()
{
  QApplication::clipboard()->setText(ui->plainTextEditOutput->toPlainText());
}

void BlockCodeFormatter::convertText(QStringList& text, QList<int> lines, QStringList symbols, const QString& leadingWhitespace)
{
  for (int i = 0; i < lines.length(); i++)
  {
    QString& string = const_cast<QString&>(text.at(lines.at(i)));
    string = string.simplified();
  }

  int lastMax = 0;

  for (int s = 0; s < symbols.length(); s++)
  {
    QMap<int, int> positions;

    for (int i = 0; i < lines.length(); i++)
    {
      QString& string = const_cast<QString&>(text.at(lines.at(i)));
      positions[lines.at(i)] = string.indexOf(symbols.at(s), lastMax);
    }

    // find maximum
    int maximum = 0;

    for (int i = 0; i < lines.length(); i++)
    {
      if (positions[lines.at(i)] > maximum)
      {
        maximum = positions[lines.at(i)];
      }
    }

    lastMax = maximum + 1;

    for (int i = 0; i < lines.length(); i++)
    {
      if (positions[lines.at(i)] < maximum)
      {
        QString& string = const_cast<QString&>(text.at(lines.at(i)));
        QString fillString((maximum - positions[lines.at(i)]), ' ');
        string = string.insert(positions[lines.at(i)], fillString);
      }
    }
  }

  for (int i = 0; i < lines.length(); i++)
  {
    QString& string = const_cast<QString&>(text.at(lines.at(i)));
    string.prepend(leadingWhitespace);
  }
}
