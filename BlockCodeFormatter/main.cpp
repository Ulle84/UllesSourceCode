#include <QFile>

int main(int argc, char* argv[])
{
  if (argc > 1)
  {
    for (int i = 1; i < argc; i++)
    {

    }
  }
}

/*
void CodeFormatter::on_pushButtonFormat_clicked()
{
  ui.plainTextEditOutput->clear();

  QStringList lines = ui.plainTextEditInput->toPlainText().split("\n");
  QStringList symbols;
  QList<int> linesToConvert;

  QString startTag = "//|";

  QString leadingWhitespace;
  bool convertNextLine = false;
  for (int i = 0; i < lines.length(); i++)
  {
    if (lines.at(i).trimmed().indexOf(startTag) == 0)
    {
      leadingWhitespace = lines.at(i).left(lines.at(i).indexOf(startTag));
      convertNextLine = true;
      symbols = lines.at(i).trimmed().mid(startTag.length()).split("|");
    }
    else if(lines.at(i).trimmed().indexOf("//") == 0)
    {
      // do nothing
    }
    else if (lines.at(i).trimmed() == "")
    {
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
    }
  }
  ui.plainTextEditOutput->appendPlainText(lines.join("\n"));
}

void CodeFormatter::convertText(QStringList &text, QList<int> lines, QStringList symbols, const QString& leadingWhitespace)
{
  for (int i = 0; i < lines.length(); i++)
  {
    QString& string = const_cast<QString&>(text.at(lines.at(i)));
    clearUnnecessaryWhiteSpace(string);
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

void CodeFormatter::clearUnnecessaryWhiteSpace( QString& input )
{
  input = input.trimmed();
  while (input.indexOf("  ") > -1)
  {
    input.replace("  ", " ");
  }
}
*/