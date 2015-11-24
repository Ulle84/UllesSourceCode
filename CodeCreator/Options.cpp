#include <QtAlgorithms>

#include "Options.h"

Options::Options() :
  folderInput("false")
{

}

void Options::sortSearchAndReplaceList()
{
  qSort(searchAndReplace.begin(), searchAndReplace.end());
}
