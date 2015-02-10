#include "ViDiagToLog4Cxx.h"
#include "ui_ViDiagToLog4Cxx.h"

ViDiagToLog4Cxx::ViDiagToLog4Cxx(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ViDiagToLog4Cxx)
{
  ui->setupUi(this);
}

ViDiagToLog4Cxx::~ViDiagToLog4Cxx()
{
  delete ui;
}

void ViDiagToLog4Cxx::on_lineEditViDiag_editingFinished()
{
  ui->lineEditLog4Cxx->clear();

    // ViDIAGX (1, "%d. ViIO-Geraet '%s' gefunden\n", i, szTestDeviceName);
    // 1st Parameter -> Testlevel -> 0 = FATAL, 1 = ERRROR, ...

    // ViDIAG0 (testlevel, string)
    // ViDIAG1 (testlevel, string, value1)
    // ViDIAG2 (testlevel, string, value1, value2)
    // ...
    // ViDIAG8 (testlevel, string, value1, value2, ..., value8)

    // --> LOG4CXX_WARN(logger, __FUNCTION__ << i << ". ViIO-Geraet '" << szTestDeviceName << "' gefunden");

    QString simplified = ui->lineEditViDiag->text().simplified();

    if (simplified.left(6) == "ViDIAG")
    {
      int leftParanthesis = simplified.indexOf("(");
      int rightParanthesis = simplified.lastIndexOf(")");

      if (leftParanthesis < 0 || rightParanthesis <  0)
      {
        return;
      }

      QStringList parameters = simplified.mid(leftParanthesis + 1, rightParanthesis - leftParanthesis - 1).split(",");

      if (parameters.count() < 2)
      {
        return;
      }

      if (parameters[1].count("%") != parameters.length() - 2)
      {
        return;
      }

      for (auto it = parameters.begin(); it != parameters.end(); it++)
      {
        *it = (*it).simplified();
      }

      QString log4CxxString;
      switch(parameters[0].toInt())
      {
      case 0:
        log4CxxString = "LOG4CXX_FATAL";
        break;
      case 1:
        log4CxxString = "LOG4CXX_ERROR";
        break;
      case 2:
        log4CxxString = "LOG4CXX_WARN";
        break;
      case 3:
        log4CxxString = "LOG4CXX_INFO";
        break;
      case 4:
        log4CxxString = "LOG4CXX_DEBUG";
        break;
      default:
        log4CxxString = "LOG4CXX_TRACE";
      }

      QString logContent;

      int parameterIndex = 2;
      while(parameters[1].contains("%"))
      {
        // todo endless loop, when string with %-sign is replaced?
        parameters[1].replace(parameters[1].indexOf("%"), 2, QString("\" << %1 << \"").arg(parameters[parameterIndex++]));
      }


      log4CxxString.append(QString("(%1, __FUNCTION__ << %2);").arg(ui->lineEditLogger->text()).arg(parameters[1]));

      ui->lineEditLog4Cxx->setText(log4CxxString);
    }
}
