#ifndef TUKIBASAR_H
#define TUKIBASAR_H

#include <QMainWindow>
#include <QStandardItemModel>

#include "ArticleManager.h"
#include "Settings.h"
#include "Evaluation.h"

namespace Ui {
class TuKiBasar;
}

class TuKiBasar : public QMainWindow
{
    Q_OBJECT

public:
    explicit TuKiBasar(QWidget *parent = 0);
    ~TuKiBasar();

private slots:
    void on_actionSettings_triggered(bool checked);
    void on_actionEvaluation_triggered(bool checked);
    void on_actionImportArticleLists_triggered(bool checked);
    void on_lineEditScannerInput_returnPressed();

private:
    Ui::TuKiBasar *ui;
    Settings m_settings;
    Evaluation m_evaluation;
    ArticleManager m_articleManager;
};

#endif // TUKIBASAR_H
