#ifndef HTMLTABLEGENERATOR_H
#define HTMLTABLEGENERATOR_H

#include <QWidget>

namespace Ui {
class HtmlTableGenerator;
}

class HtmlTableGenerator : public QWidget
{
  Q_OBJECT

public:
  explicit HtmlTableGenerator(QWidget *parent = 0);
  ~HtmlTableGenerator();

private slots:
    void updateHtmlTable();
    void update();
    void on_pushButtonAddRow_clicked();
    void on_pushButtonAddColumn_clicked();
    void on_pushButtonClearTable_clicked();
    void on_pushButtonRemoveRow_clicked();
    void on_pushButtonRemoveColumn_clicked();
    void on_tableWidget_cellChanged(int row, int column);
    void on_pushButtonCopyToClipboard_clicked();
    void on_checkBox_stateChanged(int newState);
    void on_lineEditTitle_textChanged(const QString &arg1);
    void on_lineEditId_textChanged(const QString &arg1);
    void on_spinBoxTabCount_valueChanged(int newValue);

private:
  Ui::HtmlTableGenerator *ui;
};

#endif // HTMLTABLEGENERATOR_H
