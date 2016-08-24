#include <QApplication>
#include <QClipboard>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  if (argc < 2)
  {
    return -1;
  }

  a.clipboard()->setText(QString("!%1!").arg(argv[1]));

  return 0;
}
