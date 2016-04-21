#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void sortLines();

private slots:
    void on_plainTextEditSource_textChanged();

private:


    QStringList m_textLines;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
