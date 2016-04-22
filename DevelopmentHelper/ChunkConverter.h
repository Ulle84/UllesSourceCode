#ifndef CHUNKCONVERTER_H
#define CHUNKCONVERTER_H

#include <QMap>
#include <QString>
#include <QWidget>

namespace Ui {
class ChunkConverter;
}

class ChunkConverter : public QWidget
{
  Q_OBJECT

public:
  explicit ChunkConverter(QWidget *parent = 0);
  ~ChunkConverter();

private slots:
  void on_lineEditChunkCode_returnPressed();
  void on_lineEditChunkName_returnPressed();

private:
  void setUpCharacterForCodeMap();
  void setUpCodeForCharacterMap();

  Ui::ChunkConverter *ui;

  QMap<QString, QString> m_characterForCode;
  QMap<QString, QString> m_codeForCharacter;
};

#endif // CHUNKCONVERTER_H
