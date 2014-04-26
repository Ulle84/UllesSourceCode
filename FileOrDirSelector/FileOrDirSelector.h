#ifndef FILEORDIRSELECTOR_H
#define FILEORDIRSELECTOR_H

#include <QWidget>
#include <QDir>

namespace Ui
{
class FileOrDirSelector;
}

class FileOrDirSelector : public QWidget
{
  Q_OBJECT

public:
  explicit FileOrDirSelector(QWidget* parent = 0);
  ~FileOrDirSelector();

private slots:
  void on_pushButtonSelectBaseFolder_clicked();

  void on_pushButtonSelectRelativeFolder_clicked();

  void on_pushButtonSelectRelativeFile_clicked();

  void on_pushButtonCopyBaseFolderToClipboard_clicked();

  void on_pushButtonCopyRelativeFolderToClipboard_clicked();

  void on_pushButtonCopyRelativeFileToClipboard_clicked();

  void updateLineEditFields();

  void on_lineEditBaseFolder_textEdited(const QString& arg1);

  void on_checkBoxProject_clicked(bool checked);

  void on_checkBoxSolution_clicked(bool checked);

private:
  Ui::FileOrDirSelector* ui;
  QString baseFolder;
  QString relativeFolder;
  QString relativeFile;
};

#endif // FILEORDIRSELECTOR_H
