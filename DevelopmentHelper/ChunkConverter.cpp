#include "ChunkConverter.h"
#include "ui_ChunkConverter.h"

ChunkConverter::ChunkConverter(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ChunkConverter)
{
  setUpCharacterForCodeMap();
  setUpCodeForCharacterMap();

  ui->setupUi(this);
}

ChunkConverter::~ChunkConverter()
{
  delete ui;
}

void ChunkConverter::on_lineEditChunkCode_returnPressed()
{
  QString chunkCode = ui->lineEditChunkCode->text();

  if (chunkCode.length() % 2 != 0)
  {
    return;
  }

  QString chunkName;
  for (int i = 0; i < chunkCode.length(); i += 2)
  {
    QString code = chunkCode.mid(i, 2).toUpper();
    chunkName.append(m_characterForCode[code]);
  }

  ui->lineEditChunkName->setText(chunkName);
}

void ChunkConverter::on_lineEditChunkName_returnPressed()
{
  QString chunkName = ui->lineEditChunkName->text();

  QString chunkCode;
  for (int i = 0; i < chunkName.length(); i++)
  {
    QString character = chunkName.mid(i, 1);
    chunkCode.append(m_codeForCharacter[character]);
  }

  ui->lineEditChunkCode->setText(chunkCode);
}

void ChunkConverter::setUpCharacterForCodeMap()
{
  m_characterForCode["41"] = "A";
  m_characterForCode["42"] = "B";
  m_characterForCode["43"] = "C";
  m_characterForCode["44"] = "D";
  m_characterForCode["45"] = "E";
  m_characterForCode["46"] = "F";
  m_characterForCode["47"] = "G";
  m_characterForCode["48"] = "H";
  m_characterForCode["49"] = "I";
  m_characterForCode["4A"] = "J";
  m_characterForCode["4B"] = "K";
  m_characterForCode["4C"] = "L";
  m_characterForCode["4D"] = "M";
  m_characterForCode["4E"] = "N";
  m_characterForCode["4F"] = "O";
  m_characterForCode["50"] = "P";
  m_characterForCode["51"] = "Q";
  m_characterForCode["52"] = "R";
  m_characterForCode["53"] = "S";
  m_characterForCode["54"] = "T";
  m_characterForCode["55"] = "U";
  m_characterForCode["56"] = "V";
  m_characterForCode["57"] = "W";
  m_characterForCode["58"] = "X";
  m_characterForCode["59"] = "Y";
  m_characterForCode["5A"] = "Z";

  m_characterForCode["61"] = "a";
  m_characterForCode["62"] = "b";
  m_characterForCode["63"] = "c";
  m_characterForCode["64"] = "d";
  m_characterForCode["65"] = "e";
  m_characterForCode["66"] = "f";
  m_characterForCode["67"] = "g";
  m_characterForCode["68"] = "h";
  m_characterForCode["69"] = "i";
  m_characterForCode["6A"] = "j";
  m_characterForCode["6B"] = "k";
  m_characterForCode["6C"] = "l";
  m_characterForCode["6D"] = "m";
  m_characterForCode["6E"] = "n";
  m_characterForCode["6F"] = "o";
  m_characterForCode["70"] = "p";
  m_characterForCode["71"] = "q";
  m_characterForCode["72"] = "r";
  m_characterForCode["73"] = "s";
  m_characterForCode["74"] = "t";
  m_characterForCode["75"] = "u";
  m_characterForCode["76"] = "v";
  m_characterForCode["77"] = "w";
  m_characterForCode["78"] = "x";
  m_characterForCode["79"] = "y";
  m_characterForCode["7A"] = "z";
}

void ChunkConverter::setUpCodeForCharacterMap()
{
  m_codeForCharacter["A"] = "41";
  m_codeForCharacter["B"] = "42";
  m_codeForCharacter["C"] = "43";
  m_codeForCharacter["D"] = "44";
  m_codeForCharacter["E"] = "45";
  m_codeForCharacter["F"] = "46";
  m_codeForCharacter["G"] = "47";
  m_codeForCharacter["H"] = "48";
  m_codeForCharacter["I"] = "49";
  m_codeForCharacter["J"] = "4A";
  m_codeForCharacter["K"] = "4B";
  m_codeForCharacter["L"] = "4C";
  m_codeForCharacter["M"] = "4D";
  m_codeForCharacter["N"] = "4E";
  m_codeForCharacter["O"] = "4F";
  m_codeForCharacter["P"] = "50";
  m_codeForCharacter["Q"] = "51";
  m_codeForCharacter["R"] = "52";
  m_codeForCharacter["S"] = "53";
  m_codeForCharacter["T"] = "54";
  m_codeForCharacter["U"] = "55";
  m_codeForCharacter["V"] = "56";
  m_codeForCharacter["W"] = "57";
  m_codeForCharacter["X"] = "58";
  m_codeForCharacter["Y"] = "59";
  m_codeForCharacter["Z"] = "5A";

  m_codeForCharacter["a"] = "61";
  m_codeForCharacter["b"] = "62";
  m_codeForCharacter["c"] = "63";
  m_codeForCharacter["d"] = "64";
  m_codeForCharacter["e"] = "65";
  m_codeForCharacter["f"] = "66";
  m_codeForCharacter["g"] = "67";
  m_codeForCharacter["h"] = "68";
  m_codeForCharacter["i"] = "69";
  m_codeForCharacter["j"] = "6A";
  m_codeForCharacter["k"] = "6B";
  m_codeForCharacter["l"] = "6C";
  m_codeForCharacter["m"] = "6D";
  m_codeForCharacter["n"] = "6E";
  m_codeForCharacter["o"] = "6F";
  m_codeForCharacter["p"] = "70";
  m_codeForCharacter["q"] = "71";
  m_codeForCharacter["r"] = "72";
  m_codeForCharacter["s"] = "73";
  m_codeForCharacter["t"] = "74";
  m_codeForCharacter["u"] = "75";
  m_codeForCharacter["v"] = "76";
  m_codeForCharacter["w"] = "77";
  m_codeForCharacter["x"] = "78";
  m_codeForCharacter["y"] = "79";
  m_codeForCharacter["z"] = "7A";
}
