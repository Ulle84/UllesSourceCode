#include <QProcess>

int main(int argc, char *argv[])
{
  if (argc > 1)
  {
    QString fileName = argv[1];
    int pointPos = fileName.lastIndexOf('.');

    QString program = "c:\\Program Files (x86)\\Notepad++\\notepad++.exe";

    if (pointPos > -1)
    {
      QString fileExtension = fileName.mid(pointPos + 1);


      if (fileExtension == "png")
      {
        program = "c:\\Program Files\\Greenshot\\Greenshot.exe";
      }
      else if (fileExtension == "xls")
      {
        program = "c:\\Program Files (x86)\\Microsoft Office\\Office12\\EXCEL.EXE";
      }
    }

    QProcess::startDetached(program, QStringList() << fileName);
  }
}
