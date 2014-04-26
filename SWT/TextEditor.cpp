#include "TextEditor.h"
#include "ui_TextEditor.h"

TextEditor::TextEditor(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TextEditor)
{
  ui->setupUi(this);
}

TextEditor::~TextEditor()
{
  delete ui;
}
