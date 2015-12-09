#ifndef RUNLENGTHCODE_H
#define RUNLENGTHCODE_H


#include <list>
#include "Point.h"



class RunLengthCode
{
public:
  RunLengthCode();

  appendRunLength(const RunLength& runLength);
  std::list<RunLength> getRunLengths();

private:
  std::list<RunLength> m_runLengths;
};

#endif // RUNLENGTHCODE_H
