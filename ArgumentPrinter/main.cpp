#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
  QFile file("arguments.txt");

  if (!file.open(QIODevice::WriteOnly))
  {
    return -1;
  }

  QTextStream out(&file);

  for (int i = 0; i < argc; ++i)
  {
    if (i != 0)
    {
      out << '\n';
    }
    out << argv[i];
  }
}
