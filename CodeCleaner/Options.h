#ifndef OPTIONS_H
#define OPTIONS_H

class Options
{
public:
  Options();

  void enableAll();

  bool m_removeLineDelimiters;
  bool m_removeDoubleEmptyLines;
  bool m_removeEmptyLinesBeforeClosingBracket;
  bool m_removeEmptyLinesAfterOpeningBracket;
  bool m_removeUnnecessaryNamespaceStuff;
  bool m_removeUnnecessaryStuff;
  bool m_moveCommaToRightPlace;
};

#endif // OPTIONS_H
